#include <stdio.h>
#include "Structures.c"
#include "GameEngine.h"

int main()
{
	printf("sraka\n");
	GameState gameState;
	GiveCards(13, &gameState);


	CardsQueueItem* cur = gameState.Player1Data.FirstHandCard;
	for (int i = 0; i < gameState.Player1Data.HandCardsCount; i++)
	{
		printf("%i %i\n", (int)cur -> value.Color, cur -> value.Number);
		cur = cur->previous;
	}

	printf("jea");
	return 0;
}