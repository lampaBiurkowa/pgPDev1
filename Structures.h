#pragma once

#define DECK_MAX_SIZE (52) // 4 talie * 13 kart

typedef struct Card
{
	enum { PIK, KARO, TREFL, KIER } Color;
	int Number;
} Card;

typedef struct CardQueueItem
{
	Card value;
	struct CardQueueItem* next;
	struct CardQueueItem* previous;
} CardQueueItem;

typedef struct CardsQueue
{
	CardQueueItem AllCards[DECK_MAX_SIZE];
	CardQueueItem* FirstCard;
	CardQueueItem* LastCard;
	int CardsCount;
} CardsQueue;

Card PopFrontCard(CardsQueue* queue);