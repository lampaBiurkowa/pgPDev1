#include <stdio.h>
#include "Structures.h"
#include "GameEngine.h"

void PlayGame(int deckSize, WarOption warOption, GameState *gameState)
{
	gameState -> WarOption = warOption;
	InitGame(gameState);
	GiveCards(deckSize, gameState);
	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		Battle(gameState);
		if (gameState -> Winner == &gameState -> Player1Data)
			break;
		else if (gameState -> Winner == &gameState -> Player2Data)
			break;
	}
}

int main()
{

	/*CardQueueItem *item = gameState.Player1Data.HandCards.FirstCard;
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
	printf("jea");*/

	GameState gameState;// = malloc(sizeof(GameState));
	for (int i = 0; i < 1000; i++)
	{
		PlayGame(13, WITHOUT_REFILL, &gameState);
		if (gameState.Winner == &gameState.Player1Data)
			printf("player 1 won ");
		else if (gameState.Winner == &gameState.Player2Data)
			printf("player 2 won ");
		
		printf("Turns Count: %i\n", gameState.TurnsCount);
	}
	return 0;
}