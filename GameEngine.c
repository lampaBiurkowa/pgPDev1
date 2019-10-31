#include "GameEngine.h"
#include <ctime>

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

Card* generateCardsInRandomOrder(int cardsPerColors)
{
	srand(time(NULL));

	Card cardsGiven[DECK_MAX_SIZE];
	int cardsGivenCount = 0;
	while (cardsGivenCount < cardsPerColors * COLORS_COUNT)
	{
		Card card = generateSingleRandomCard(cardsPerColors);
		if (!cardAlreadyGiven(&card, cardsGiven, cardsGivenCount))
		{
			cardsGiven[cardsGivenCount] = card;
			cardsGivenCount++;
		}
	}

	return cardsGiven;
}

void assignCardsToPlayers(int cardsPerColors, Card cardsInRandomOrder[], GameState *gameState)
{
	for (int i = 0; i < cardsPerColors * COLORS_COUNT; i++)
	{
		/*if (i % 2 == 0)
			gameState -> Player1Data.HandCards.
		else*/
	}
}

void GiveCards(int cardsPerColors, GameState *gameState)
{
	Card cards[DECK_MAX_SIZE] = generateCardsInRandomOrder(cardsPerColors);
	assignCardsToPlayers(cards, gameState);
}