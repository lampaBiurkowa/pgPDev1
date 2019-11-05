#include "GameEngine.h"
#include <time.h>

#include <stdio.h> //TODO remove

void takeCardsFromStack(CardsQueue *destination, CardsQueue *source)
{
	int cardsToTakeAmount = source -> CardsCount;
	for (int i = 0; i < cardsToTakeAmount; i++)
	{
		Card card = PopFrontCard(source);
		PushBackCard(destination, card);
	}
}

void handleBattleWon(PlayerData *winner, PlayerData *looser)
{
	takeCardsFromStack(&winner -> HandCards, &winner -> StackCards);
	takeCardsFromStack(&winner -> HandCards, &looser -> StackCards);
}

void addCardToStack(PlayerData *player)
{
	Card card = PopFrontCard(&player -> HandCards);
	PushFrontCard(&player -> StackCards, card);
}

void handleVictory(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount == 0)
		gameState -> Winner = &gameState -> Player2Data;
	else if (gameState -> Player2Data.HandCards.CardsCount == 0)
		gameState -> Winner = &gameState -> Player1Data;
}

void handleComparingCards(GameState *gameState)
{
	if (gameState -> Winner != NULL)
		return;

	int player1CardPower = gameState -> Player1Data.StackCards.FirstCard -> value.Number;
	int player2CardPower = gameState -> Player2Data.StackCards.FirstCard -> value.Number;

	CardQueueItem *item = gameState -> Player1Data.HandCards.FirstCard;

	if (player1CardPower > player2CardPower)
		handleBattleWon(&gameState -> Player1Data, &gameState -> Player2Data);
	else if (player1CardPower < player2CardPower)
		handleBattleWon(&gameState -> Player2Data, &gameState -> Player1Data);
	else
		War(gameState);

	handleVictory(gameState);
}

void Battle(GameState *gameState)
{
	gameState -> TurnsCount++;
	addCardToStack(&gameState -> Player1Data);
	addCardToStack(&gameState -> Player2Data);

	handleComparingCards(gameState);
}

int finishGameIfWarNotPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player2Data;
		return 0;
	}
	else if (gameState -> Player2Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player1Data;
		return 0;
	}

	return 1;
}

int performWarOptionWithoutRefillIfPossible(GameState *gameState)
{
	if (!finishGameIfWarNotPossible(gameState))
		return 0;

	for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
	{
		addCardToStack(&gameState -> Player1Data);
		addCardToStack(&gameState -> Player2Data);
		gameState -> TurnsCount++;
	}

	return 1;
}

void War(GameState *gameState)
{
	if (gameState -> WarOption == WITHOUT_REFILL)
		if (performWarOptionWithoutRefillIfPossible(gameState))
			handleComparingCards(&gameState -> Player1Data, &gameState -> Player2Data);
}

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

Card *generateCardsInRandomOrder(int cardsPerColors, Card arrayToFill[])
{
	srand(time(NULL));

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

	return arrayToFill;
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

void GiveCards(int cardsPerColors, GameState *gameState)
{
	Card *cards = malloc(sizeof(Card) * DECK_MAX_SIZE);
	cards = generateCardsInRandomOrder(cardsPerColors, cards);
	assignCardsToPlayer(cardsPerColors, cards, &gameState -> Player1Data.HandCards, 0);
	assignCardsToPlayer(cardsPerColors, cards, &gameState -> Player2Data.HandCards, 1);
}

void initQueues(PlayerData *playerData)
{
	InitCardsQueue(&playerData -> HandCards);
	InitCardsQueue(&playerData -> StackCards);
}

void InitGame(GameState *gameState)
{
	gameState -> TurnsCount = 0;
	gameState -> Winner = NULL;
	initQueues(&gameState -> Player1Data);
	initQueues(&gameState -> Player2Data);
}