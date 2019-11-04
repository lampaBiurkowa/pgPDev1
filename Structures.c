#include "Structures.h"
#define NULL (0)

Card PopFrontCard(CardsQueue *queue)
{
	Card value = queue -> FirstCard -> value;
	queue -> FirstCard = queue -> FirstCard -> previous;
	queue -> CardsCount--;

	return value;
}

void PushFrontCard(CardsQueue *queue, Card value)
{
	CardQueueItem newItem;
	newItem.next = NULL;
	newItem.value = value;
	newItem.previous = queue -> FirstCard;

	queue -> AllCards[queue -> CardsCount] = newItem;
	CardQueueItem* newItemPtr = &queue -> AllCards[queue -> CardsCount];

	if (queue -> FirstCard != NULL)
		queue -> FirstCard -> next = &queue -> AllCards[queue -> CardsCount];

	queue -> FirstCard = newItemPtr;
	queue -> CardsCount++;
}

void PushBackCard(CardsQueue* queue, Card value)
{
	CardQueueItem newItem;
	newItem.next = queue -> LastCard;
	newItem.value = value;
	newItem.previous = NULL;

	queue -> AllCards[queue -> CardsCount] = newItem;
	CardQueueItem* newItemPtr = &queue -> AllCards[queue -> CardsCount];

	if (queue -> LastCard != NULL)
		queue -> LastCard -> previous = &queue -> AllCards[queue -> CardsCount];

	queue -> LastCard = newItemPtr;
	queue -> CardsCount++;
}

void ClearCards(CardsQueue *queue)
{
	CardQueueItem *currentItem = queue -> FirstCard;
	for (int i = 0; i < queue -> CardsCount; i++)
	{
		CardQueueItem *nextItem = currentItem -> next;
		delete(currentItem);
		currentItem = nextItem;
	}

	queue -> CardsCount = 0;
	delete(queue -> FirstCard);
	delete(queue -> LastCard);
}