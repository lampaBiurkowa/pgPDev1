#include "CoreGameEngine.h"

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

void AddFirstCardToStack(PlayerData *player)
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

void HandleComparingCards(GameState *gameState)
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

int finishGameIfWarNotPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player2Data;
		return FALSE;
	}
	else if (gameState -> Player2Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player1Data;
		return FALSE;
	}

	return TRUE;
}

void initQueues(PlayerData *playerData)
{
	InitCardsQueue(&playerData -> HandCards);
	InitCardsQueue(&playerData -> StackCards);
}

void InitGame(GameState *gameState, WarOption warOption, int randomSeed)
{
	gameState -> Player1Data.UsedEnemyCardsInWar = 0;
	gameState -> Player2Data.UsedEnemyCardsInWar = 0;
	gameState -> RandomSeed = randomSeed;
	gameState -> TurnsCount = 0;
	gameState -> WarOption = warOption;
	gameState -> Winner = NULL;

	initQueues(&gameState -> Player1Data);
	initQueues(&gameState -> Player2Data);
}