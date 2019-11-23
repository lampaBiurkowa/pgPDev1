#include "GameDataPrinter.h"

void PrintCardsQueue(CardsQueue *queue)
{
	CardQueueItem *item = queue -> FirstCard;
	for (int i = 0; i < queue -> CardsCount; i++)
	{
		if (i % CARDS_TO_SHOW_PER_ROW == 0 && i != 0)
			printf("\n");

		printf("|%i %s| ", item -> value.Number, GetCardSuitName(item -> value.Color));
		item = item -> previous;
	}
	printf("\n");
}