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
	srand(time(NULL) + seed);

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

int getCardNumberOccurrences(int numberConsidered, Card cardsDisabled[], int cardsDisabledCount)
{
	int occurences = COLORS_COUNT;

	for (int i = 0; i < cardsDisabledCount; i++)
		if (cardsDisabled[i].Number == numberConsidered)
			occurences--;

	return occurences;
}

int getMaxRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount)
{
	int maxRankReachable = 0;
	int cardsUsedCount = 0;
	int currentNumber = MAX_CARD_NUMBER;
	while (currentNumber >= MIN_CARD_NUMBER_POINTING && cardsUsedCount < cardsAmount)
	{
		int currentPoint = currentNumber - MIN_CARD_NUMBER_POINTING + 1;
		int occurences = getCardNumberOccurrences(currentNumber, cardsDisabled, cardsDisabledCount);
		maxRankReachable += occurences * currentPoint;
		cardsUsedCount += occurences;
		currentNumber--;
	}

	return maxRankReachable;
}

int getMinRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount)
{
	int minRankReachable = 0;
	int cardsUsedCount = 0;
	int currentNumber = MIN_CARD_NUMBER;
	while (currentNumber <= MAX_CARD_NUMBER && cardsUsedCount < cardsAmount)
	{
		int currentPoint = GetCardRank(currentNumber);
		int occurences = getCardNumberOccurrences(currentNumber, cardsDisabled, cardsDisabledCount);
		minRankReachable += occurences * currentPoint;
		cardsUsedCount += occurences;
		currentNumber++;
	}

	return minRankReachable;
}

int wasDecisionValid(int cardsToGiveCount, Card cardsUsed[], int cardsGivenCount, int rank, int currentRank)
{
	int missingRank = rank - currentRank;
	int decisionValid = TRUE;
	if (getMaxRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount) < missingRank)
		decisionValid = FALSE;
	else if (getMinRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount) > missingRank)
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

		int missingCardsCount = cardsToGiveCount - cardsGivenCount;
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

void ShuffleCards(CardsQueue *queue)
{
	srand(time(NULL));

	int newIndexesPlacement[DECK_MAX_SIZE / 2]; //TODO new int[] ?
	
	int indexesPlacedCount = 0;
	int cardsCount = queue -> CardsCount;
	while (indexesPlacedCount < cardsCount)
	{
		int index = rand() % cardsCount;
		if (indexAlreadyPlaced(index, newIndexesPlacement, indexesPlacedCount))
			continue;
		
		newIndexesPlacement[indexesPlacedCount] = index;
		indexesPlacedCount++;
	}

	Card cards[DECK_MAX_SIZE / 2]; //TODO new int[] ?
	for (int i = 0; i < cardsCount; i++)
		cards[i] = PopFrontCard(queue);

	for (int i = 0; i < cardsCount; i++)
		PushBackCard(queue, cards[newIndexesPlacement[i]]);
}

void GetCardsForRank(int rank, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	generateCardsForRank(gameState -> CardsPerColor, rank, cards, gameState -> RandomSeed);
	assignCardsToPlayers(gameState -> CardsPerColor, cards, gameState);
	ShuffleCards(&gameState -> Player1Data.HandCards);
	ShuffleCards(&gameState -> Player2Data.HandCards);
}