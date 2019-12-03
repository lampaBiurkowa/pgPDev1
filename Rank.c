#include "Rank.h"
#include "Structures.h"
#include "CardsDeliverer.h"

int GetCardRank(int cardNumber, int minCardNumberPointing)
{
	if (cardNumber < minCardNumberPointing)
		return 0;

	return cardNumber - minCardNumberPointing + 1;
}

Card GetRandomCardForRank(int rank, int minCardNumberPointing)
{
	Card card;
	if (rank > 0)
		card.Number = rank + minCardNumberPointing - 1;
	else
		card.Number = (rand() % (minCardNumberPointing - MIN_CARD_NUMBER)) + MIN_CARD_NUMBER;
	card.Color = rand() % COLORS_COUNT;

	return card;
}

int GetQueueRank(CardsQueue *queue, int minCardNumberPointing)
{
	int output = 0;
	CardQueueItem *item = queue -> FirstCard;
	if (item == NULL)
		return output;

	if (item -> value.Number >= minCardNumberPointing)
		output += item -> value.Number - minCardNumberPointing + 1;

	for (int i = 1; i < queue -> CardsCount; i++)
	{
		item = item -> previous;
		if (item -> value.Number >= minCardNumberPointing)
			output += item -> value.Number - minCardNumberPointing + 1;
	}

	return output;
}

int GetArrayRank(Card array[], int size, int minCardNumberPointing)
{
	int output = 0;

	for (int i = 0; i < size; i++)
		if (array[i].Number >= minCardNumberPointing)
			output += array[i].Number - minCardNumberPointing + 1;

	return output;
}

int getCardNumberOccurrences(int numberConsidered, Card cardsDisabled[], int cardsDisabledCount)
{
	int occurences = COLORS_COUNT;

	for (int i = 0; i < cardsDisabledCount; i++)
		if (cardsDisabled[i].Number == numberConsidered)
			occurences--;

	return occurences;
}

int GetMaxRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount, int minCardNumberPointing)
{
	int maxRankReachable = 0, cardsUsedCount = 0, currentNumber = MAX_CARD_NUMBER;
	while (currentNumber >= minCardNumberPointing && cardsUsedCount < cardsAmount)
	{
		int currentPoint = currentNumber - minCardNumberPointing + 1;
		int occurences = getCardNumberOccurrences(currentNumber, cardsDisabled, cardsDisabledCount);
		if (occurences > cardsAmount - cardsUsedCount)
			occurences = cardsAmount - cardsUsedCount;

		maxRankReachable += occurences * currentPoint;
		cardsUsedCount += occurences;
		currentNumber--;
	}

	return maxRankReachable;
}

int GetMinRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount, int minCardNumberPointing)
{
	int minRankReachable = 0;
	int cardsUsedCount = 0;
	int currentNumber = MIN_CARD_NUMBER;
	while (currentNumber <= MAX_CARD_NUMBER && cardsUsedCount < cardsAmount)
	{
		int currentPoint = GetCardRank(currentNumber, minCardNumberPointing);
		int occurences = getCardNumberOccurrences(currentNumber, cardsDisabled, cardsDisabledCount);
		if (occurences > cardsAmount - cardsUsedCount)
			occurences = cardsAmount - cardsUsedCount;

		minRankReachable += occurences * currentPoint;
		cardsUsedCount += occurences;
		currentNumber++;
	}

	return minRankReachable;
}

int GetMaxRankForDeckSize(int cardsPerColor, int minCardNumberPointing)
{
	Card *cards = malloc(0);
	return GetMaxRankReachable((cardsPerColor * COLORS_COUNT) / 2, cards, 0, minCardNumberPointing);
}

int GetMinRankForDeckSize(int cardsPerColor, int minCardNumberPointing)
{
	Card *cards = malloc(0);
	return GetMinRankReachable((cardsPerColor * COLORS_COUNT) / 2, cards, 0, minCardNumberPointing);
}