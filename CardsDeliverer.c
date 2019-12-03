#include "CardsDeliverer.h"
#include "Rank.h"

Card generateSingleRandomCard(int cardsPerColors)
{
	int colorId = rand() % COLORS_COUNT;
	int cardNumber = rand() % cardsPerColors + MAX_CARD_NUMBER - cardsPerColors + 1;
	Card card;
	card.Color = colorId;
	card.Number = cardNumber;
	return card;
}

int arrayContainsCard(Card *cardConsidered, Card array[], int size)
{
	for (int i = 0; i < size; i++)
		if (array[i].Color == cardConsidered -> Color && array[i].Number == cardConsidered -> Number)
			return TRUE;

	return FALSE;
}

void generateCardsInRandomOrder(int cardsPerColors, Card arrayToFill[])
{
	int cardsGivenCount = 0;
	while (cardsGivenCount < cardsPerColors * COLORS_COUNT)
	{
		Card card = generateSingleRandomCard(cardsPerColors);
		if (!arrayContainsCard(&card, arrayToFill, cardsGivenCount))
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
	generateCardsInRandomOrder(gameState -> CardsPerColor, cards);
	assignCardsToPlayers(gameState -> CardsPerColor, cards, gameState);
}

int getSmallerNumberIfPossible(Card *card, int diff, Card array[], int size)
{
	int target = card -> Number + diff; //diff < 0
	if (target < MIN_CARD_NUMBER)
		target = MIN_CARD_NUMBER;

	for (int i = target; i < card -> Number; i++)
	{
		int occurances = 0;
		for (int j = 0; j < size; j++)
		{
			if (array[j].Number == i)
				occurances++;
		}
		if (occurances < COLORS_COUNT)
			return i;
	}

	return card -> Number;
}

CardColor getUnusedColor(int number, Card array[], int size)
{
	Card card;
	card.Number = number;
	for (int i = 0; i < COLORS_COUNT; i++)
	{
		card.Color = i;
		if (!arrayContainsCard(&card, array, size))
			return i;
	}
}

int getBiggerNumberIfPossible(Card *card, int diff, Card array[], int size)
{
	int target = card -> Number + diff; //diff < 0
	if (target > MAX_CARD_NUMBER)
		target = MAX_CARD_NUMBER;

	for (int i = target; i > card -> Number; i--)
	{
		int occurances = 0;
		for (int j = 0; j < size; j++)
		{
			if (array[j].Number == i)
				occurances++;
		}
		if (occurances < COLORS_COUNT)
			return i;
	}

	return card -> Number;
}

Card getBetterCardIfPossible(Card *card, int diff, Card array[], int size)
{
	int newNumber;
	if (diff > 0)
		newNumber = getBiggerNumberIfPossible(card, diff, array, size);
	else
		newNumber = getSmallerNumberIfPossible(card, diff, array, size);

	Card result;
	if (newNumber == card -> Number)
	{
		result.Number = card -> Number;
		result.Color = card -> Color;
		return result;
	}

	result.Number = newNumber;
	result.Color = getUnusedColor(newNumber, array, size);
	return result;
}

void generateCardsForRank(int cardsPerColor, int rank, int minCardNumberPointing, Card arrayToFill[])
{
	int cardsCount = cardsPerColor * (COLORS_COUNT / 2);
	int i = 0;
	while (i < cardsCount)
	{
		Card card = generateSingleRandomCard(cardsPerColor);
		if (arrayContainsCard(&card, arrayToFill, i))
			continue;

		arrayToFill[i] = card;
		i++;
	}

	int currentRank = GetArrayRank(arrayToFill, cardsCount, minCardNumberPointing);
	while (currentRank != rank)
	{
		int index = rand() % cardsCount;
		int diff = rank - currentRank;
		arrayToFill[index] = getBetterCardIfPossible(&arrayToFill[index], diff, arrayToFill, cardsCount);
		currentRank = GetArrayRank(arrayToFill, cardsCount, minCardNumberPointing);
	}
}

void assignRemainingCards(int cardsPerColor, Card arrayPartlyFilled[])
{
	int cardsAlreadyGivenCount = (cardsPerColor * COLORS_COUNT) / 2;
	while (cardsAlreadyGivenCount < cardsPerColor * COLORS_COUNT)
	{
		Card card = generateSingleRandomCard(cardsPerColor);
		if (arrayContainsCard(&card, arrayPartlyFilled, cardsAlreadyGivenCount))
			continue;

		arrayPartlyFilled[cardsAlreadyGivenCount] = card;
		cardsAlreadyGivenCount++;
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

void GetCardsForRank(GameState *gameState, int rank, int minCardNumberPointing)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);

	if (rank < GetMinRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing))
		rank = GetMinRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing);
	else if (rank > GetMaxRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing))
		rank = GetMaxRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing);

	generateCardsForRank(gameState -> CardsPerColor, rank, minCardNumberPointing, cards);
	assignRemainingCards(gameState -> CardsPerColor, cards);
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