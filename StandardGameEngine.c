#include "StandardGameEngine.h"
#include <time.h>

void Battle(GameState *gameState)
{
	gameState -> TurnsCount++;
	AddFirstCardToStack(&gameState -> Player1Data);
	AddFirstCardToStack(&gameState -> Player2Data);

	HandleComparingCards(gameState);
}

int performWarOptionWithoutRefillIfPossible(GameState *gameState)
{
	if (!finishGameIfWarNotPossible(gameState))
		return FALSE;

	for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
	{
		AddFirstCardToStack(&gameState -> Player1Data);
		AddFirstCardToStack(&gameState -> Player2Data);
		gameState -> TurnsCount++;
	}

	return TRUE;
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
		AddFirstCardToStack(helpingPlayer);

	playerNeedingHelp -> UsedEnemyCardsInWar = 1;
}

int performWarOptionWithRefillIfPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount <= 2) //TODO && > 0?
	{
		if (gameState -> Player1Data.UsedEnemyCardsInWar == 0)
		{
			buildStackWithHelp(&gameState -> Player2Data, &gameState -> Player1Data);
			gameState -> TurnsCount++;
		}
		else
			return FALSE;
	}
	else if (gameState -> Player2Data.HandCards.CardsCount <= 2)
	{
		if (gameState -> Player2Data.UsedEnemyCardsInWar == 0)
		{
			buildStackWithHelp(&gameState -> Player1Data, &gameState -> Player2Data);
			gameState -> TurnsCount++;
		}
		else
			return FALSE;
	}
	else
	{
		for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
		{
			AddFirstCardToStack(&gameState -> Player1Data);
			AddFirstCardToStack(&gameState -> Player2Data);
			gameState -> TurnsCount++;
		}
	}

	return TRUE;
}

void War(GameState *gameState)
{
	if (gameState -> WarOption == WITHOUT_REFILL)
	{
		if (performWarOptionWithoutRefillIfPossible(gameState))
			HandleComparingCards(gameState);
	}
	else if (gameState -> WarOption == WITH_REFILL)
	{
		if (performWarOptionWithRefillIfPossible(gameState))
			HandleComparingCards(gameState);
	}
}