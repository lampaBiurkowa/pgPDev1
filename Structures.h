#pragma once

typedef struct Card
{
	enum { PIK, KARO, TREFL, KIER } Color;
	int Number;
} Card;

typedef struct CardsQueue
{
	Card value;
	struct CardsQueue* first;
	struct CardsQueue* last;
	struct CardsQueue* next;
	struct CardsQueue* previous;
} CardsQueue;