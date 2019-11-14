#pragma once

#define DECK_MAX_SIZE (52) // 52 = 4 talie * 13 kart
#define NULL (0)
#define FALSE (0)
#define TRUE (1)

typedef struct Card
{
	enum { PIK, KARO, TREFL, KIER } Color;
	int Number;
	int Id;
} Card;

typedef struct CardQueueItem
{
	Card value;
	struct CardQueueItem *next;
	struct CardQueueItem *previous;
} CardQueueItem;

typedef struct CardsQueue
{
	int QueueItemsAllocations[DECK_MAX_SIZE];
	CardQueueItem AllCards[DECK_MAX_SIZE];
	CardQueueItem *FirstCard;
	CardQueueItem *LastCard;
	int CardsCount;
} CardsQueue;


void InitCardsQueue(CardsQueue *queue);
Card PopFrontCard(CardsQueue *queue);
void PushFrontCard(CardsQueue *queue, Card value);
void PushBackCard(CardsQueue *queue, Card value);