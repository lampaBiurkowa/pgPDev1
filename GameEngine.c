#include "GameEngine.h"
#include <time.h>

#include <stdio.h> //TODO remove

void takeCardsFromStack(CardsQueue *destination, CardsQueue *source)
{
	int cardsToTakeAmount = source -> CardsCount;
	for (int i = 0; i < cardsToTakeAmount; i++)
	{
		Card card = PopFrontCard(source);
		PushBackCard(destination, card);
	}
}

void handleBattleWon(PlayerData *winner, PlayerData *looser)
{
	takeCardsFromStack(&winner -> HandCards, &winner -> StackCards);
	takeCardsFromStack(&winner -> HandCards, &looser -> StackCards);
}

void addCardToStack(PlayerData *player)
{
	Card card = PopFrontCard(&player -> HandCards);
	PushFrontCard(&player -> StackCards, card);
}

void handleVictory(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount == 0)
		gameState -> Winner = &gameState -> Player2Data;
	else if (gameState -> Player2Data.HandCards.CardsCount == 0)
		gameState -> Winner = &gameState -> Player1Data;
}

void handleComparingCards(GameState *gameState)
{
	if (gameState -> Winner != NULL)
		return;

	int player1CardPower = gameState -> Player1Data.StackCards.FirstCard -> value.Number;
	int player2CardPower = gameState -> Player2Data.StackCards.FirstCard -> value.Number;

	CardQueueItem *item = gameState -> Player1Data.HandCards.FirstCard;

	if (player1CardPower > player2CardPower)
		handleBattleWon(&gameState -> Player1Data, &gameState -> Player2Data);
	else if (player1CardPower < player2CardPower)
		handleBattleWon(&gameState -> Player2Data, &gameState -> Player1Data);
	else
		War(gameState);

	handleVictory(gameState);
}

void Battle(GameState *gameState)
{
	gameState -> TurnsCount++;
	addCardToStack(&gameState -> Player1Data);
	addCardToStack(&gameState -> Player2Data);

	handleComparingCards(gameState);
}

int finishGameIfWarNotPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player2Data;
		return 0;
	}
	else if (gameState -> Player2Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player1Data;
		return 0;
	}

	return 1;
}

int performWarOptionWithoutRefillIfPossible(GameState *gameState)
{
	if (!finishGameIfWarNotPossible(gameState))
		return 0;

	for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
	{
		addCardToStack(&gameState -> Player1Data);
		addCardToStack(&gameState -> Player2Data);
		gameState -> TurnsCount++;
	}

	return 1;
} 

void addCardToStackWithHelp(PlayerData *helpingPlayer, PlayerData *playerNeedingHelp)
{
	Card card = PopFrontCard(&helpingPlayer -> HandCards);
	PushFrontCard(&playerNeedingHelp -> StackCards, card);
}

void buildStackWithHelp(PlayerData *helpingPlayer, PlayerData *playerNeedingHelp)
{
	for (int i = 0; i <= CARDS_TAKING_PART_IN_WAR - playerNeedingHelp -> HandCards.CardsCount; i++)
		addCardToStackWithHelp(helpingPlayer, playerNeedingHelp);

	for (int i = 0; i <= CARDS_TAKING_PART_IN_WAR - playerNeedingHelp -> HandCards.CardsCount; i++)
		addCardToStack(helpingPlayer);

	playerNeedingHelp -> UsedEnemyCardsInWar = 1;
}

int performWarOptionWithRefillIfPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount <= 2) //TODO & > 0?
	{
		if (gameState -> Player1Data.UsedEnemyCardsInWar == 0)
		{
			buildStackWithHelp(&gameState -> Player2Data, &gameState -> Player1Data);
			gameState -> TurnsCount++;
		}
		else
			return 0;
	}
	else if (gameState -> Player2Data.HandCards.CardsCount <= 2)
	{
		if (gameState -> Player2Data.UsedEnemyCardsInWar == 0)
		{
			buildStackWithHelp(&gameState -> Player1Data, &gameState -> Player2Data);
			gameState -> TurnsCount++;
		}
		else
			return 0;
	}
	else
	{
		for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
		{
			addCardToStack(&gameState -> Player1Data);
			addCardToStack(&gameState -> Player2Data);
			gameState -> TurnsCount++;
		}
	}

	return 1;
}

void War(GameState *gameState)
{
	if (gameState -> WarOption == WITHOUT_REFILL)
	{
		if (performWarOptionWithoutRefillIfPossible(gameState))
			handleComparingCards(&gameState -> Player1Data, &gameState -> Player2Data);
	}
	else if (gameState -> WarOption == WITH_REFILL)
	{
		if (performWarOptionWithRefillIfPossible(gameState))
			handleComparingCards(&gameState -> Player1Data, &gameState -> Player2Data);
	}
}

void initQueues(PlayerData *playerData)
{
	InitCardsQueue(&playerData -> HandCards);
	InitCardsQueue(&playerData -> StackCards);
}

void InitGame(GameState *gameState)
{
	gameState -> TurnsCount = 0;
	gameState -> Winner = NULL;
	gameState -> Player1Data.UsedEnemyCardsInWar = 0;
	gameState -> Player2Data.UsedEnemyCardsInWar = 0;
	initQueues(&gameState -> Player1Data);
	initQueues(&gameState -> Player2Data);
}