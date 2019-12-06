#include "SmartGameEngine.h"

void smartSelectRandomly(CardsQueue *ownHandCards)
{
	if (rand() % CARDS_TO_CHOOSE_FROM_COUNT == 0)
		SwapFrontTwoCards(ownHandCards);
}

void smartSelectDefensively(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	Card firstCard = ownHandCards -> FirstCard -> value;
	Card secondCard = ownHandCards -> FirstCard -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;
	if (opponentCard.Number == secondCard.Number)
		return; //nie robic swapa powodujacego wojne
	if (opponentCard.Number == firstCard.Number)
		SwapFrontTwoCards(ownHandCards);
	else if (firstCard.Number > opponentCard.Number && secondCard.Number > opponentCard.Number && firstCard.Number > secondCard.Number)
		SwapFrontTwoCards(ownHandCards);
	else if (firstCard.Number > opponentCard.Number && secondCard.Number < opponentCard.Number)
		SwapFrontTwoCards(ownHandCards);
}

void smartSelectOffensively(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	Card firstCard = ownHandCards -> FirstCard -> value;
	Card secondCard = ownHandCards -> FirstCard -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;
	if (opponentCard.Number == firstCard.Number)
		return;
	if (opponentCard.Number == secondCard.Number)
		SwapFrontTwoCards(ownHandCards);
	if (firstCard.Number > opponentCard.Number && secondCard.Number < opponentCard.Number)
		return; //wykonac przebicie
	if (firstCard.Number > secondCard.Number)
		SwapFrontTwoCards(ownHandCards);
}

int makeSwapInEfficentStrategy(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	int VERY_STRONG_CARD_MIN_NUMBER = 12;
	int STRONG_CARD_MIN_NUMBER = 10;
	int WEAK_CARD_MAX_NUMBER = 7;

	Card firstCard = ownHandCards -> FirstCard -> value;
	Card secondCard = ownHandCards -> FirstCard -> previous -> value;
	if (ownHandCards -> CardsCount == 2)
		return FALSE;
	Card thirdCard = ownHandCards -> FirstCard -> previous -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;

	int *opponentVeryStrongCardsCount = (int *)malloc(sizeof(int) * (MAX_CARD_NUMBER - VERY_STRONG_CARD_MIN_NUMBER + 1));
	for (int i = VERY_STRONG_CARD_MIN_NUMBER; i <= MAX_CARD_NUMBER; i++)
	{
		opponentVeryStrongCardsCount[i - VERY_STRONG_CARD_MIN_NUMBER] = GetCardNumberOccurrencesInQueue(ownHandCards, i);
		if (opponentCard.Number == i)
			opponentVeryStrongCardsCount[i - VERY_STRONG_CARD_MIN_NUMBER]++;
	}

	if (firstCard.Number > opponentCard.Number && secondCard.Number > opponentCard.Number)
	{
		if (firstCard.Number > secondCard.Number)
			return TRUE;
	}
	else if (firstCard.Number == opponentCard.Number || secondCard.Number == opponentCard.Number)
	{
		if (secondCard.Number == opponentCard.Number && thirdCard.Number >= VERY_STRONG_CARD_MIN_NUMBER && firstCard.Number < thirdCard.Number)
			return TRUE;
		if (firstCard.Number == opponentCard.Number && (thirdCard.Number < VERY_STRONG_CARD_MIN_NUMBER || secondCard.Number > thirdCard.Number))
			return TRUE;
	}
	else if (firstCard.Number > opponentCard.Number || secondCard.Number > opponentCard.Number)
	{
		if (opponentCard.Number <= WEAK_CARD_MAX_NUMBER)
		{
			if (firstCard.Number < secondCard.Number && secondCard.Number < STRONG_CARD_MIN_NUMBER)
				return TRUE;
			else if (firstCard.Number > secondCard.Number &&firstCard.Number >= STRONG_CARD_MIN_NUMBER)
				return TRUE;
		}
		else
		{
			if (firstCard.Number < secondCard.Number)
				return TRUE;
		}
	}
	else
	{
		if (firstCard.Number > secondCard.Number)
			return TRUE;
	}

	return FALSE;
}

void smartSelectEfficently(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	if (makeSwapInEfficentStrategy(ownHandCards, opponentStackCards))
		SwapFrontTwoCards(ownHandCards);
}

Card smartSelectByUser(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	CardQueueItem *firstCardItem = ownHandCards -> FirstCard;
	Card firstCard = firstCardItem -> value;
	Card secondCard = firstCardItem -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;
	printf("Karta na szcycie stosu przeciwnika: |%i %s|\n", opponentCard.Number, GetCardSuitName(opponentCard.Id));
	printf("> Wybierz jedna z kart (podaj 1 lub 2): 1 - |%i %s|, 2 - |%i %s|:", firstCard.Number, GetCardSuitName(firstCard.Color), secondCard.Number, GetCardSuitName(secondCard.Color));
	int choice;
	scanf_s("%i", &choice);
	if (choice == 2)
		SwapFrontTwoCards(ownHandCards);
}

void chooseCardWithStrategy(PlayerData *startingPlayer, PlayerData *selectingPlayer)
{
	//printf("SUDGAHDSASD %i \n", selectingPlayer -> Strategy);
	if (selectingPlayer -> Strategy == DEFENSIVE)
		smartSelectDefensively(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
	else if (selectingPlayer -> Strategy == OFFENSIVE)
		smartSelectOffensively(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
	else if (selectingPlayer -> Strategy == USER)
		smartSelectByUser(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
	else if (selectingPlayer -> Strategy == EFFICENT)
		smartSelectEfficently(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
	else if (selectingPlayer -> Strategy == RANDOMLY)
		smartSelectRandomly(&selectingPlayer -> HandCards);
}

void appendStackInSmartBattle(PlayerData *startingPlayer, PlayerData *selectingPlayer)
{
	AddFirstCardToStack(startingPlayer);
	if (selectingPlayer -> HandCards.CardsCount >= 2)
		chooseCardWithStrategy(startingPlayer, selectingPlayer);
	AddFirstCardToStack(selectingPlayer);
}

void SmartBattle(GameState *gameState, PlayerData *startingPlayer)
{
	gameState -> TurnsCount++;
	
	if (startingPlayer == &gameState -> Player1Data)
		appendStackInSmartBattle(&gameState -> Player1Data, &gameState -> Player2Data);
	else
		appendStackInSmartBattle(&gameState -> Player2Data, &gameState -> Player1Data);

	HandleComparingCards(gameState);
}