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

Card smartSelectByUser(CardsQueue *ownHandCards, CardsQueue *opponentStackCards)
{
	CardQueueItem *firstCardItem = ownHandCards -> FirstCard;
	Card firstCard = firstCardItem -> value;
	Card secondCard = firstCardItem -> previous -> value;
	Card opponentCard = opponentStackCards -> FirstCard -> value;
	printf("Twoj wybor!\n");
	printf("Karta na szcycie stosu przeciwnika: |%i %s|\n", opponentCard.Number, GetCardSuitName(opponentCard.Id));
	printf("Wybierz jedna z kart (podaj 1 lub 2): 1 - |%i %s|, 2 - |%i %s|:", firstCard.Number, GetCardSuitName(firstCard.Color), secondCard.Number, GetCardSuitName(secondCard.Color));
	int choice;
	scanf_s("%i", &choice);
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
	else
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