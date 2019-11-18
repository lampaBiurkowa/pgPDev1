#include "SmartGameEngine.h"

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

void chooseCardWithStrategy(PlayerData *startingPlayer, PlayerData *selectingPlayer)
{
	if (selectingPlayer -> Strategy == DEFENSIVE)
		smartSelectDefensively(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
	else if (selectingPlayer -> Strategy == OFFENSIVE)
		smartSelectOffensively(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
	else
		smartSelectRandomly(&selectingPlayer -> HandCards, &startingPlayer -> StackCards);
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
	Card *cards = malloc(sizeof(Card) * CARDS_TO_CHOOSE_FROM_COUNT);

	if (startingPlayer == &gameState -> Player1Data)
		appendStackInSmartBattle(&gameState -> Player1Data, &gameState -> Player2Data);
	else
		appendStackInSmartBattle(&gameState -> Player2Data, &gameState -> Player1Data);

	HandleComparingCards(gameState);
}