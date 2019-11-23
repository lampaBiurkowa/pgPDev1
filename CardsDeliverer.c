#include "CardsDeliverer.h"
#include "Rank.h"

Card generateSingleRandomCard(int cardsPerColors)
{
	int colorId = rand() % COLORS_COUNT;
	int cardNumber = rand() % cardsPerColors + YOUNGEST_CARD_NUMBER;
	Card card;
	card.Color = colorId;
	card.Number = cardNumber;
	return card;
}

int cardAlreadyGiven(Card *cardConsidered, Card cardsGiven[], int cardsGivenCount)
{
	for (int i = 0; i < cardsGivenCount; i++)
		if (cardsGiven[i].Color == cardConsidered -> Color && cardsGiven[i].Number == cardConsidered -> Number)
			return TRUE;

	return FALSE;
}

void generateCardsInRandomOrder(int cardsPerColors, Card arrayToFill[], unsigned int seed)
{
	srand(time(NULL) + seed * 7); //TODO ?

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
}

CardQueueItem *handleCreatingNewCardsQueueItem(Card value, CardQueueItem *currentItem, Card cardsInRandomOrder[], CardsQueue *cardsQueue)
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

void assignCardsToPlayers(int cardsPerColors, Card cardsInRandomOrder[], GameState *gameState)
{
	int cardsTotalCount = cardsPerColors * COLORS_COUNT;
	for (int i = 0; i < cardsTotalCount; i++)
		if (i < cardsTotalCount / 2)
			PushBackCard(&gameState -> Player1Data.HandCards, cardsInRandomOrder[i]);
		else
			PushBackCard(&gameState -> Player2Data.HandCards, cardsInRandomOrder[i]);

}

void GiveCards(GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	generateCardsInRandomOrder(gameState -> CardsPerColor, cards, gameState -> RandomSeed);
	assignCardsToPlayers(gameState -> CardsPerColor, cards, gameState);
}

int wasDecisionValid(int cardsToGiveCount, Card cardsUsed[], int cardsGivenCount, int rank, int currentRank)
{
	int missingRank = rank - currentRank;
	int decisionValid = TRUE;
	if (GetMaxRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount) < missingRank)
		decisionValid = FALSE;
	else if (GetMinRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount) > missingRank)
		decisionValid = FALSE;
	else if (currentRank > rank)
		decisionValid = FALSE;

	return decisionValid;
}

void generateCardsForRank(int cardsPerColors, int rank, Card arrayToFill[], unsigned int seed)
{
	srand(time(NULL) + seed);

	int cardsGivenCount = 0, currentRank = 0, cardsToGiveCount = (cardsPerColors * COLORS_COUNT) / 2;
	while (cardsGivenCount < cardsToGiveCount)
	{
		Card card = generateSingleRandomCard(cardsPerColors);
		if (cardAlreadyGiven(&card, arrayToFill, cardsGivenCount))
			continue;

		arrayToFill[cardsGivenCount] = card;
		cardsGivenCount++;
		currentRank += GetCardRank(card.Number);

		int missingCardsCount = cardsToGiveCount - cardsGivenCount + 1;
		if (!wasDecisionValid(missingCardsCount, arrayToFill, cardsGivenCount, rank, currentRank))
		{
			cardsGivenCount--;
			currentRank -= GetCardRank(card.Number);
		}
	}
}

int indexAlreadyPlaced(int index, int indexesAlreadyPlaced[], int indexesPlacedCount)
{
	for (int i = 0; i < indexesPlacedCount; i++)
		if (indexesAlreadyPlaced[i] == index)
			return TRUE;

	return FALSE;
}

void generateNewIndexesPlacement(int arrayToFill[], int cardsCount)
{
	srand(time(NULL));

	int indexesPlacedCount = 0;
	while (indexesPlacedCount < cardsCount)
	{
		int index = rand() % cardsCount;
		if (indexAlreadyPlaced(index, arrayToFill, indexesPlacedCount))
			continue;

		arrayToFill[indexesPlacedCount] = index;
		indexesPlacedCount++;
	}
}

void assignShuffledCards(int cardsCount, CardsQueue *queue, int newIndexesPlacement[])
{
	Card *cards = malloc(sizeof(Card) * cardsCount);
	for (int i = 0; i < cardsCount; i++)
		cards[i] = PopFrontCard(queue);

	for (int i = 0; i < cardsCount; i++)
		PushBackCard(queue, cards[newIndexesPlacement[i]]);
}

void ShuffleCards(CardsQueue *queue)
{
	int cardsCount = queue -> CardsCount;
	int *newIndexesPlacement = malloc(sizeof(int) * cardsCount);
	generateNewIndexesPlacement(newIndexesPlacement, cardsCount);
	assignShuffledCards(cardsCount, queue, newIndexesPlacement);
}

void GetCardsForRank(int rank, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);

	if (rank < GetMinRankForDeckSize(gameState -> CardsPerColor))
		rank = GetMinRankForDeckSize(gameState -> CardsPerColor);
	else if (rank > GetMaxRankForDeckSize(gameState -> CardsPerColor))
		rank = GetMaxRankForDeckSize(gameState -> CardsPerColor);

	generateCardsForRank(gameState -> CardsPerColor, rank, cards, gameState -> RandomSeed);
	assignCardsToPlayers(gameState -> CardsPerColor, cards, gameState);
	ShuffleCards(&gameState -> Player1Data.HandCards);
	ShuffleCards(&gameState -> Player2Data.HandCards);
}

void AssignCardNumbersFromArray(GameState *gameState, int *cardNumbers, int cardsCount)
{
	Card card;
	for (int i = 0; i < cardsCount / 2; i++)
	{
		card.Number = cardNumbers[i];
		int occurances = GetCardNumberOccurrencesInQueue(&gameState -> Player1Data.HandCards, card.Number);
		card.Color = (CardColor)occurances; //from range 0 - 3
		PushBackCard(&gameState -> Player1Data.HandCards, card);
	}
	for (int i = cardsCount / 2; i < cardsCount; i++)
	{
		card.Number = cardNumbers[i];
		int occurances = GetCardNumberOccurrencesInQueue(&gameState -> Player1Data.HandCards, card.Number) + GetCardNumberOccurrencesInQueue(&gameState -> Player2Data.HandCards, card.Number);
		card.Color = (CardColor)occurances; //from range 0 - 3
		PushBackCard(&gameState -> Player2Data.HandCards, card);
	}
}