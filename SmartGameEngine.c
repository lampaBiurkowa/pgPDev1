#include "SmartGameEngine.h"
#include "conio.h"

Card smartSelectRandomly(CardsQueue *ownHandCards)
{
	static int seed;
	srand(time(NULL) + seed);
	if (rand() % CARDS_TO_CHOOSE_FROM_COUNT == 0)
		SwapFrontTwoCards(ownHandCards);

	seed = (seed + 1) % 10000;
}

Card smartSelectDefensively(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	CardQueueItem *firstCardItem = ownHandCards -> FirstCard;
	Card firstCard = firstCardItem -> value;
	Card secondCard = firstCardItem -> previous -> value;
	if (opponentStackCards -> FirstCard -> value.Number == firstCard.Number || secondCard.Number < firstCard.Number)
		SwapFrontTwoCards(ownHandCards);
}

Card smartSelectOffensively(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	CardQueueItem *firstCardItem = ownHandCards -> FirstCard;
	Card firstCard = firstCardItem -> value;
	Card secondCard = firstCardItem -> previous -> value;
	if (opponentStackCards -> FirstCard -> value.Number == secondCard.Number || secondCard.Number > firstCard.Number)
		SwapFrontTwoCards(ownHandCards);
}

int makeSwapInEfficentStrategy(PlayerData *efficentPlayer, PlayerData *opponent)
{
	const int VERY_STRONG_CARD_MIN_NUMBER = 12;
	const int STRONG_CARD_MIN_NUMBER = 10;
	const int WEAK_CARD_MAX_NUMBER = 7;

	Card firstCard = efficentPlayer -> HandCards.FirstCard -> value;
	Card secondCard = efficentPlayer -> HandCards.FirstCard -> previous -> value;
	if (efficentPlayer -> HandCards.CardsCount == 2)
		return FALSE; //TODO to nie tak
	Card thirdCard = efficentPlayer -> HandCards.FirstCard -> previous -> previous -> value;
	Card opponentCard = opponent -> StackCards.FirstCard -> value;

	int *opponentVeryStrongCardsCount = (int *)malloc(sizeof(int) * (MAX_CARD_NUMBER - VERY_STRONG_CARD_MIN_NUMBER + 1));
	for (int i = VERY_STRONG_CARD_MIN_NUMBER; i <= MAX_CARD_NUMBER; i++)
	{
		opponentVeryStrongCardsCount[i - VERY_STRONG_CARD_MIN_NUMBER] = GetCardNumberOccurrencesInQueue(&efficentPlayer -> HandCards, i);
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

Card smartSelectEfficently(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	CardQueueItem *firstCardItem = ownHandCards -> FirstCard;
	Card firstCard = firstCardItem -> value;
	Card secondCard = firstCardItem -> previous -> value;
	Card thirdCard = firstCardItem -> previous -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;

	if (1)//makeSwapInEfficentStrategy())
		SwapFrontTwoCards(ownHandCards);
}

Card smartSelectByUser(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	CardQueueItem *firstCardItem = ownHandCards -> FirstCard;
	Card firstCard = firstCardItem -> value;
	Card secondCard = firstCardItem -> previous -> value;
	Card thirdCard = firstCardItem -> previous -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;
	printf("Twoj wybor!\n");
	printf("Karta na szcycie stosu przeciwnika: |%i %s|\n", opponentCard.Number, GetCardSuitName(opponentCard.Id));
	printf("Wybierz jedna z kart (podaj 1 lub 2): 1 - |%i %s|, 2 - |%i %s|:", firstCard.Number, GetCardSuitName(firstCard.Color), secondCard.Number, GetCardSuitName(secondCard.Color));
	int choice = 2;//makeSwapInEfficentStrategy(firstCard, secondCard, thirdCard, opponentCard) + 1;
	//scanf_s("%i", &choice);
	printf("wybrano %i", choice);
	_getch();
	if (choice == 2)
		SwapFrontTwoCards(ownHandCards);
}

void chooseCardWithStrategy(PlayerData *startingPlayer, PlayerData *selectingPlayer)
{
	if (selectingPlayer -> Strategy == DEFENSIVE) //TODO SWITCH ?
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