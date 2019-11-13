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
		if (cardsGiven[i].Color == cardConsidered -> Color && cardsGiven[i].Number == cardConsidered->Number)
			return 1;

	return 0;
}

void generateCardsInRandomOrder(int cardsPerColors, Card arrayToFill[], unsigned int seed)
{
	srand(time(NULL) + seed * 7);

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

void assignCardsToPlayer(int cardsPerColors, Card cardsInRandomOrder[], CardsQueue *cardsQueue, int playerIndex) //player index 0 or 1
{
	PushBackCard(cardsQueue, cardsInRandomOrder[playerIndex]);

	for (int i = 2; i < cardsPerColors * COLORS_COUNT; i++)
		if (i % 2 == playerIndex)
			PushBackCard(cardsQueue, cardsInRandomOrder[i]);
}

void GiveCards(GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	generateCardsInRandomOrder(gameState -> CardsPerColor, cards, gameState -> RandomSeed);
	assignCardsToPlayer(gameState -> CardsPerColor, cards, &gameState -> Player1Data.HandCards, 0);
	assignCardsToPlayer(gameState -> CardsPerColor, cards, &gameState -> Player2Data.HandCards, 1);
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
		int currentPoint = currentNumber < MIN_CARD_NUMBER_POINTING ? 0 : currentNumber - MIN_CARD_NUMBER_POINTING + 1;
		int occurences = getCardNumberOccurrences(currentNumber, cardsDisabled, cardsDisabledCount);
		minRankReachable += occurences * currentPoint;
		cardsUsedCount += occurences;
		currentNumber++;
	}

	return minRankReachable;
}

void generateCardsForRank(int cardsPerColors, int rank, Card arrayToFill[], unsigned int seed)
{
	srand(time(NULL) + seed * 7);

	int cardsGivenCount = 0;
	int currentRank = 0;
	while (cardsGivenCount < (cardsPerColors * COLORS_COUNT) / 2)
	{
		Card card = generateSingleRandomCard(cardsPerColors);
		if (!cardAlreadyGiven(&card, arrayToFill, cardsGivenCount))
		{
			arrayToFill[cardsGivenCount] = card;
			cardsGivenCount++;
			if (card.Number >= MIN_CARD_NUMBER_POINTING)
				currentRank += card.Number - MIN_CARD_NUMBER_POINTING + 1;

			printf("u jea %i goal:%i current:%i max:%i min:%i\n", cardsGivenCount, rank, currentRank, getMaxRankReachable((cardsPerColors * COLORS_COUNT) / 2 - cardsGivenCount, arrayToFill, cardsGivenCount), getMinRankReachable((cardsPerColors * COLORS_COUNT) / 2 - cardsGivenCount, arrayToFill, cardsGivenCount));
			if (getMaxRankReachable((cardsPerColors * COLORS_COUNT) / 2 - cardsGivenCount, arrayToFill, cardsGivenCount) < rank - currentRank)
			{
				cardsGivenCount--;
				currentRank -= card.Number - MIN_CARD_NUMBER_POINTING + 1;
			}
			else if (getMinRankReachable((cardsPerColors * COLORS_COUNT) / 2 - cardsGivenCount, arrayToFill, cardsGivenCount) > rank - currentRank)
			{
				cardsGivenCount--;
				currentRank -= card.Number - MIN_CARD_NUMBER_POINTING + 1;
			}
			else if (currentRank > rank)
			{
				cardsGivenCount--;
				currentRank -= card.Number - MIN_CARD_NUMBER_POINTING + 1;
			}
		}
	}
}

void GetCardsForRank(int rank, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	generateCardsForRank(gameState -> CardsPerColor, rank, cards, gameState -> RandomSeed);
}