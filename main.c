#include <stdio.h>
#include "Structures.h"
#include "GameEngine.h"

int main()
{
	printf("sraka\n");
	GameState gameState;
	gameState.WarOption = WITHOUT_REFILL;
	InitGame(&gameState);
	GiveCards(13, &gameState);
	printf("co jest");

	CardQueueItem *item = gameState.Player1Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player1Data.HandCards.CardsCount; i++)
	{
		printf("%i %i|", item -> value.Color, item -> value.Number);
		item = item -> previous;
	}
	printf("\n bb \n");
	item = gameState.Player2Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player2Data.HandCards.CardsCount; i++)
	{
		printf("%i %i|", item -> value.Color, item -> value.Number);
		item = item -> previous;
	}
	printf("jea");

	while (gameState.Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState.Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		Battle(&gameState);
		if (gameState.Winner == &gameState.Player1Data)
		{
			printf("player 1 won");
			break;
		}
		else if (gameState.Winner == &gameState.Player2Data)
		{
			printf("player 2 won");
			break;
		}
		printf("player1: %i player2: %i (%i:%i)\n", gameState.Player1Data.HandCards.CardsCount, gameState.Player2Data.HandCards.CardsCount, gameState.Player1Data.StackCards.CardsCount, gameState.Player2Data.StackCards.CardsCount);
	}

	item = gameState.Player1Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player1Data.HandCards.CardsCount; i++)
	{
		printf("%i %i|", item -> value.Color, item -> value.Number);
		item = item -> previous;
	}
	printf("\n bb \n");
	item = gameState.Player2Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player2Data.HandCards.CardsCount; i++)
	{
		printf("%i %i|", item -> value.Color, item -> value.Number);
		item = item -> previous;
	}
	printf("jea");
	return 0;
}