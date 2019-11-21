#include "Rank.h"
#include "Structures.h"
#include "CardsDeliverer.h"

int GetCardRank(int cardNumber)
{
	if (cardNumber < MIN_CARD_NUMBER_POINTING)
		return 0;

	return cardNumber - MIN_CARD_NUMBER_POINTING + 1;
}

int GetPlayerRank(PlayerData *player)
{
	int output = 0;
	CardQueueItem *item = player -> HandCards.FirstCard;
	if (item == NULL)
		return output;

	if (item -> value.Number >= MIN_CARD_NUMBER_POINTING)
		output += item -> value.Number - MIN_CARD_NUMBER_POINTING + 1;

	for (int i = 1; i < player -> HandCards.AllCards; i++)
	{
		item = item -> next;
		if (item -> value.Number >= MIN_CARD_NUMBER_POINTING)
			output += item -> value.Number - MIN_CARD_NUMBER_POINTING + 1;
	}

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

int GetMaxRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount)
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

int GetMinRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount)
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

int GetMaxRankForDeckSize(int cardsPerColor)
{
	Card *cards = malloc(0);
	return GetMaxRankReachable((cardsPerColor * COLORS_COUNT) / 2, cards, 0);
}

int GetMinRankForDeckSize(int cardsPerColor)
{
	Card *cards = malloc(0);
	return GetMinRankReachable((cardsPerColor * COLORS_COUNT) / 2, cards, 0);
}