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

void assignCardsToPlayers(int cardsPerColors, Card cardsInRandomOrder[], GameState *gameState)
{
	gameState ->Player1Data.HandCardsCount = 0;
	CardsQueueItem playerFirstItem;
	playerFirstItem.next = NULL;
	playerFirstItem.value = cardsInRandomOrder[0];
	gameState -> Player1Data.AllCards[gameState -> Player1Data.HandCardsCount] = playerFirstItem;
	gameState -> Player1Data.FirstHandCard = &gameState -> Player1Data.AllCards[gameState -> Player1Data.HandCardsCount];
	CardsQueueItem *currentItem = &gameState -> Player1Data.AllCards[gameState -> Player1Data.HandCardsCount];
	gameState -> Player1Data.HandCardsCount++;

	for (int i = 2; i < cardsPerColors * COLORS_COUNT; i++)
	{
		if (i % 2 == 0)
		{
			CardsQueueItem item;
			item.next = currentItem;
			item.value = cardsInRandomOrder[i];
			gameState -> Player1Data.AllCards[gameState -> Player1Data.HandCardsCount] = item;
			currentItem->previous = &gameState -> Player1Data.AllCards[gameState -> Player1Data.HandCardsCount];
			currentItem = currentItem -> previous;
			gameState -> Player1Data.HandCardsCount++;
		}
	}

	currentItem -> previous = NULL;
	gameState -> Player1Data.LastHandCard = currentItem;
}

void GiveCards(int cardsPerColors, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	cards = generateCardsInRandomOrder(cardsPerColors, cards);
	for (int i = 0; i < cardsPerColors * COLORS_COUNT; i++)
	{
		printf("%i %i \n", cards[i].Color, cards[i].Number);
	}
	printf("\n");
	assignCardsToPlayers(cardsPerColors, cards, gameState);
}