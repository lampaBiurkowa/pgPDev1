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

CardsQueueItem* handleCreatingNewCardsQueueItem(Card value, CardsQueueItem *currentItem, Card cardsInRandomOrder[], PlayerData *playerData)
{
	CardsQueueItem item;
	item.next = currentItem;
	item.value = value;
	playerData -> AllCards[playerData -> HandCardsCount] = item;

	if (currentItem == NULL)
		currentItem = &playerData -> AllCards[playerData -> HandCardsCount];
	else
	{
		currentItem -> previous = &playerData -> AllCards[playerData -> HandCardsCount];
		currentItem = currentItem -> previous;
	}

	playerData -> HandCardsCount++;
	return currentItem;
}

void assignCardsToPlayer(int cardsPerColors, Card cardsInRandomOrder[], PlayerData *playerData, int playerIndex) //player index 0 or 1
{
	playerData -> HandCardsCount = 0;
	CardsQueueItem* currentItem = NULL;
	currentItem = handleCreatingNewCardsQueueItem(cardsInRandomOrder[playerIndex], currentItem, cardsInRandomOrder, playerData);
	playerData -> FirstHandCard = currentItem;

	for (int i = 2; i < cardsPerColors * COLORS_COUNT; i++)
		if (i % 2 == playerIndex)
			currentItem = handleCreatingNewCardsQueueItem(cardsInRandomOrder[i], currentItem, cardsInRandomOrder, playerData);

	currentItem -> previous = NULL;
	playerData -> LastHandCard = currentItem;
}

void GiveCards(int cardsPerColors, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	cards = generateCardsInRandomOrder(cardsPerColors, cards);
	assignCardsToPlayer(cardsPerColors, cards, &gameState -> Player1Data, 0);
	assignCardsToPlayer(cardsPerColors, cards, &gameState -> Player2Data, 1);
}