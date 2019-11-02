#pragma once

typedef struct Card
{
	enum { PIK, KARO, TREFL, KIER } Color;
	int Number;
} Card;

typedef struct CardsQueueItem
{
	Card value;
	struct CardsQueueItem* next;
	struct CardsQueueItem* previous;
} CardsQueueItem;