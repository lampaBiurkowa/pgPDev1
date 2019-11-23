#pragma once

#define DECK_MAX_SIZE (52) // 52 = 4 talie * 13 kart
#define COLORS_COUNT (4)
#define NULL (0)
#define FALSE (0)
#define TRUE (1)

#include <stdio.h> //TODO remove

typedef enum { PIK, KARO, TREFL, KIER } CardColor;

typedef struct Card
{
	CardColor Color;
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

void ClearCards(CardsQueue *queue);
const char *GetCardSuitName(CardColor color);
int GetCardNumberOccurrencesInQueue(CardsQueue *queue, int numberConsidered);
void InitCardsQueue(CardsQueue *queue);
void MoveQueueToQueue(CardsQueue *destination, CardsQueue *source);
Card PopFrontCard(CardsQueue *queue);
void PushFrontCard(CardsQueue *queue, Card value);
void PushBackCard(CardsQueue *queue, Card value);
void SwapFrontTwoCards(CardsQueue *queue);