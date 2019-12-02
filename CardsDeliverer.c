#include "CardsDeliverer.h"
#include "Rank.h"

Card generateSingleRandomCard(int cardsPerColors)
{
	int colorId = rand() % COLORS_COUNT; //TODO rand() dziala?
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

int wasDecisionValid(int cardsToGiveCount, Card cardsUsed[], int cardsGivenCount, int rank, int minCardNumberPointing, int currentRank)
{
	int missingRank = rank - currentRank;

	//printf("MAX: %i < %i\n", GetMaxRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount, minCardNumberPointing), missingRank);
	if (GetMaxRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount, minCardNumberPointing) < missingRank)
		return FALSE;
	//printf("MIN: %i > %i\n", GetMinRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount, minCardNumberPointing), missingRank);
	if (GetMinRankReachable(cardsToGiveCount, cardsUsed, cardsGivenCount, minCardNumberPointing) > missingRank)
		return FALSE;
	if (currentRank > rank)
		return FALSE;

	return TRUE;
}

int getMinRank(int minCardPointingNumber, Card cardsUnassigned[], int mask[], int size)
{
	int minIndex = -1;
	int min = MAX_CARD_NUMBER - minCardPointingNumber + 1;
	for (int i = 0; i < size; i++)
		if (GetCardRank(cardsUnassigned[i].Number, minCardPointingNumber) < min && mask[i] == FALSE)
		{
			min = GetCardRank(cardsUnassigned[i].Number, minCardPointingNumber);
			minIndex = i;
		}

	mask[minIndex] = TRUE;
	return min;
}

int ujea(int missingRank, int minCardPointingNumber, Card cardsUnassigned[], int size)
{
	if (missingRank < 0)
		return FALSE;

	int totalSum = 0;
	for (int i = 0; i < size; i++)
		totalSum += GetCardRank(cardsUnassigned[i].Number, minCardPointingNumber);

	int *mask = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
		mask[i] = FALSE;

	for (int i = 0; i < size; i++)
	{
		if (totalSum == missingRank)
			return TRUE;
		int z = getMinRank(minCardPointingNumber, cardsUnassigned, mask, size);
		totalSum -= z;
		printf("zbijam sume o:%i tera %i ma byc: %i \n", z, totalSum, missingRank);
	}
	
	return FALSE;
}

void jea(int cardsPerColor, int rank, int minCardNumberPointing, Card arrayToFill[], unsigned int seed)
{
	srand(time(NULL) + seed);
	Card *cardsUnassigned = (Card *)malloc(sizeof(Card) * cardsPerColor * COLORS_COUNT);
	for (int i = 0; i < cardsPerColor; i++)
		for (int j = 0; j < 4; j++)
		{
			cardsUnassigned[i * 4 + j].Number = MAX_CARD_NUMBER - cardsPerColor + 1 + i;
			cardsUnassigned[i * 4 + j].Color = j;
		}

	int cardsGivenCount = 0, currentRank = 0, cardsToGiveCount = (cardsPerColor * COLORS_COUNT) / 2;
	while (cardsGivenCount < cardsToGiveCount)
	{
		Card card = generateSingleRandomCard(cardsPerColor);
		if (cardAlreadyGiven(&card, arrayToFill, cardsGivenCount))
			continue;

		arrayToFill[cardsGivenCount] = card;
		cardsGivenCount++;
		currentRank += GetCardRank(card.Number, minCardNumberPointing);
		int missingCardsCount = cardsToGiveCount - cardsGivenCount;
		printf("Wybieram %i %i - ", card.Number, card.Color);
		if (!ujea(rank - currentRank, minCardNumberPointing, cardsUnassigned, cardsPerColor * COLORS_COUNT))
		{
			printf("zla decyzja\n");
			for (int i = 0; i < cardsGivenCount; i++)
				printf(" %i", arrayToFill[i].Number);
			printf("\n");
			cardsGivenCount--;
			currentRank -= GetCardRank(card.Number, minCardNumberPointing);
		}
		else
			printf("dobra decyzja\n");
	}

}

void generateCardsForRank(int cardsPerColors, int rank, int minCardNumberPointing, Card arrayToFill[], unsigned int seed)
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
		currentRank += GetCardRank(card.Number, minCardNumberPointing);
		int missingCardsCount = cardsToGiveCount - cardsGivenCount;
		//printf("nie wyczymie given: %i misisng: %i rank: %i\n", cardsGivenCount, currentRank - rank, rank);
		if (!wasDecisionValid(missingCardsCount, arrayToFill, cardsGivenCount, rank, minCardNumberPointing, currentRank))
		{
			cardsGivenCount--;
			currentRank -= GetCardRank(card.Number, minCardNumberPointing);
		}
	}
}

void assignRemainingCards(int cardsPerColors, Card arrayPartlyFilled[])
{
	int cardsAlreadyGivenCount = (cardsPerColors * COLORS_COUNT) / 2;
	while (cardsAlreadyGivenCount < cardsPerColors * COLORS_COUNT)
	{
		Card card = generateSingleRandomCard(cardsPerColors);
		if (cardAlreadyGiven(&card, arrayPartlyFilled, cardsAlreadyGivenCount))
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

void GetCardsForRank(GameState *gameState, int rank, int minCardNumberPointing)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);

	if (rank < GetMinRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing))
		rank = GetMinRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing);
	else if (rank > GetMaxRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing))
		rank = GetMaxRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing);

	int x = 0;
	while (GetPlayerRank(&gameState -> Player1Data, minCardNumberPointing) != rank)
	{
		ClearCards(&gameState -> Player1Data.HandCards);
		ClearCards(&gameState -> Player2Data.HandCards);
		cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
		jea(gameState -> CardsPerColor, rank, minCardNumberPointing, cards, gameState -> RandomSeed + x++);

		//printf("?????????????4\n");
		assignRemainingCards(gameState -> CardsPerColor, cards);
		assignCardsToPlayers(gameState -> CardsPerColor, cards, gameState);
		//printf("a\n %i == %i", GetPlayerRank(&gameState -> Player1Data, minCardNumberPointing), rank);
	}
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