#include "Structures.h"

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

Card PopFrontCard(CardsQueue *queue)
{
	Card value = queue -> FirstCard -> value;
	queue -> FirstCard = queue -> FirstCard -> previous;
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
	{
		queue -> QueueItemsAllocations[i] = 0;
		CardQueueItem *nextItem = currentItem -> next;
		free(currentItem);
		currentItem = nextItem;
	}

	InitCardsQueue(queue);
}
