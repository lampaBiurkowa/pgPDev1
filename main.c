#include <stdio.h>
#include "Structures.h"
#include "GameEngine.h"

int main()
{
	printf("sraka\n");
	GameState gameState;
	GiveCards(13, &gameState);

	CardQueueItem* cur = gameState.Player1Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player1Data.HandCards.CardsCount; i++)
	{
		printf("%i %i\n", (int)cur -> value.Color, cur -> value.Number);
		cur = cur->previous;
	}

	printf("jea");
	return 0;
}