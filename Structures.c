#include "Structures.h"

void UpdateSrand()
{
	static int seed;
	srand(time(NULL) + seed++);
	if (seed > 10000)
		seed = 0;
}

void InitCardsQueue(CardsQueue *queue)
{
	for (int i = 0; i < DECK_MAX_SIZE; i++)
		queue -> QueueItemsAllocations[i] = 0;

	queue -> CardsCount = 0;
	queue -> FirstCard = NULL;
	queue -> LastCard = NULL;
}

CardQueueItem *allocateCardQueueItem(CardsQueue *queue, CardQueueItem item)
{
	for (int i = 0; i < DECK_MAX_SIZE; i++)
		if (!queue -> QueueItemsAllocations[i])
		{
			item.value.Id = i;
			queue -> AllCards[i] = item;
			queue -> QueueItemsAllocations[i] = 1;
			return &queue -> AllCards[i];
		}

	return NULL;
}

Card PopBackCard(CardsQueue *queue)
{
	Card value = queue -> LastCard -> value;
	queue -> LastCard = queue -> LastCard -> next;

	if (queue -> CardsCount == 0)
		queue -> FirstCard = NULL;

	queue -> QueueItemsAllocations[value.Id] = 0;
	queue -> CardsCount--;
	return value;
}

Card PopFrontCard(CardsQueue *queue)
{
	Card value = queue -> FirstCard -> value;
	queue -> FirstCard = queue -> FirstCard -> previous;
	
	if (queue -> CardsCount == 0)
		queue -> LastCard = NULL;

	queue -> QueueItemsAllocations[value.Id] = 0;
	queue -> CardsCount--;
	return value;
}

void PushBackCard(CardsQueue *queue, Card value)
{
	CardQueueItem newItem;
	newItem.next = queue -> LastCard;
	newItem.value = value;
	newItem.previous = NULL;
	CardQueueItem *newItemPtr = allocateCardQueueItem(queue, newItem);

	if (queue -> LastCard)
		queue -> LastCard -> previous = newItemPtr;

	queue -> LastCard = newItemPtr;
	if (queue -> CardsCount == 0)
		queue -> FirstCard = newItemPtr;

	queue -> CardsCount++;
}

void PushFrontCard(CardsQueue *queue, Card value)
{
	CardQueueItem newItem;
	newItem.next = NULL;
	newItem.value = value;
	newItem.previous = queue -> FirstCard;
	CardQueueItem *newItemPtr = allocateCardQueueItem(queue, newItem);

	if (queue -> FirstCard)
		queue -> FirstCard -> next = newItemPtr;

	queue -> FirstCard = newItemPtr;
	if (queue -> CardsCount == 0)
		queue -> LastCard = newItemPtr;

	queue -> CardsCount++;
}

void ClearCards(CardsQueue *queue)
{
	CardQueueItem *currentItem = queue -> FirstCard;
	for (int i = 0; i < queue -> CardsCount; i++)
		queue -> QueueItemsAllocations[i] = 0;

	InitCardsQueue(queue);
}

void SwapFrontTwoCards(CardsQueue *queue)
{
	Card firstCard = PopFrontCard(queue);
	Card secondCard = PopFrontCard(queue);
	PushFrontCard(queue, firstCard);
	PushFrontCard(queue, secondCard);
}

void MoveQueueToQueue(CardsQueue *destination, CardsQueue *source)
{
	int cardsToTakeAmount = source -> CardsCount;
	for (int i = 0; i < cardsToTakeAmount; i++)
		PushBackCard(destination, PopBackCard(source));
}

const char *GetCardSuitName(CardColor color)
{
	switch (color)
	{
	case KARO:
		return "KARO";
	case KIER:
		return "KIER";
	case PIK:
		return "PIK";
	case TREFL:
		return "TREFL";
	default:
		return "???";
	}
}

int GetCardNumberOccurrencesInQueue(CardsQueue *queue, int numberConsidered)
{
	int occurences = 0;

	CardQueueItem *item = queue -> FirstCard;
	for (int i = 0; i < queue -> CardsCount; i++)
	{
		if (item -> value.Number == numberConsidered)
			occurences++;

		item = item -> previous;
	}

	return occurences;
}

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

	if (queue -> CardsCount == 0)
		printf("Brak kart :(");

	printf("\n");
}