#include "GameEngine.h"
#include <time.h>

#include <stdio.h> //TODO remove

void Battle(PlayerData* player1, PlayerData* player2)
{
	
}

int cardAlreadyGiven(Card *cardConsidered, Card cardsGiven[], int cardsGivenCount)
{
	for (int i = 0; i < cardsGivenCount; i++)
		if (cardsGiven[i].Color == cardConsidered->Color && cardsGiven[i].Number == cardConsidered->Number)
			return 1;

	return 0;
}

Card generateSingleRandomCard(int cardsPerColors)
{
	int colorId = rand() % COLORS_COUNT;
	int cardNumber = rand() % cardsPerColors + YOUNGEST_CARD_NUMBER;
	Card card;
	card.Color = colorId;
	card.Number = cardNumber;

	return card;
}

Card* generateCardsInRandomOrder(int cardsPerColors, Card arrayToFill[])
{
	srand(time(NULL));

	int cardsGivenCount = 0;
	while (cardsGivenCount < cardsPerColors * COLORS_COUNT)
	{
		Card card = generateSingleRandomCard(cardsPerColors);
		if (!cardAlreadyGiven(&card, arrayToFill, cardsGivenCount))
		{
			arrayToFill[cardsGivenCount] = card;
			cardsGivenCount++;
		}
	}

	return arrayToFill;
}

CardQueueItem* handleCreatingNewCardsQueueItem(Card value, CardQueueItem *currentItem, Card cardsInRandomOrder[], CardsQueue *cardsQueue)
{
	CardQueueItem item;
	item.next = currentItem;
	item.value = value;
	cardsQueue -> AllCards[cardsQueue -> CardsCount] = item;

	if (currentItem == NULL)
		currentItem = &cardsQueue -> AllCards[cardsQueue -> CardsCount];
	else
	{
		currentItem -> previous = &cardsQueue -> AllCards[cardsQueue -> CardsCount];
		currentItem = currentItem -> previous;
	}

	cardsQueue -> CardsCount++;
	return currentItem;
}

void assignCardsToPlayer(int cardsPerColors, Card cardsInRandomOrder[], CardsQueue *cardsQueue, int playerIndex) //player index 0 or 1
{
	cardsQueue -> CardsCount = 0;
	CardQueueItem* currentItem = NULL;
	currentItem = handleCreatingNewCardsQueueItem(cardsInRandomOrder[playerIndex], currentItem, cardsInRandomOrder, cardsQueue);
	cardsQueue -> FirstCard = currentItem;

	for (int i = 2; i < cardsPerColors * COLORS_COUNT; i++)
		if (i % 2 == playerIndex)
			currentItem = handleCreatingNewCardsQueueItem(cardsInRandomOrder[i], currentItem, cardsInRandomOrder, cardsQueue);

	currentItem -> previous = NULL;
	cardsQueue -> LastCard = currentItem;
}

void GiveCards(int cardsPerColors, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	cards = generateCardsInRandomOrder(cardsPerColors, cards);
	assignCardsToPlayer(cardsPerColors, cards, &gameState -> Player1Data.HandCards, 0);
	assignCardsToPlayer(cardsPerColors, cards, &gameState -> Player2Data.HandCards, 1);
}