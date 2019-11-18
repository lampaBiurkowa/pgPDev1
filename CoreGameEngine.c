#include "CoreGameEngine.h"
#include "CardsDeliverer.h"

void getShuffledStackCards(CardsQueue *allStackCards, PlayerData *player1, PlayerData *player2)
{	
	MoveQueueToQueue(allStackCards, &player1 -> StackCards);
	MoveQueueToQueue(allStackCards, &player2 -> StackCards);
	ShuffleCards(allStackCards);
}

void handleBattleWon(PlayerData *winner, PlayerData *looser, GameRules gameRules)
{
	if (gameRules == STANDARD)
	{
		MoveQueueToQueue(&winner -> HandCards, &winner -> StackCards);
		MoveQueueToQueue(&winner -> HandCards, &looser -> StackCards);
	}
	else
	{
		CardsQueue shuffledStackCards;
		InitCardsQueue(&shuffledStackCards);
		getShuffledStackCards(&shuffledStackCards, winner, looser);
		MoveQueueToQueue(&winner -> HandCards, &shuffledStackCards);
	}
}

void AddFirstCardToStack(PlayerData *player)
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

void HandleComparingCards(GameState *gameState)
{
	if (gameState -> Winner != NULL)
		return;

	//printf("p1sc: ");
	CardQueueItem *item = gameState -> Player1Data.StackCards.FirstCard;
	for (int i = 0; i < gameState -> Player1Data.StackCards.CardsCount; i++)
	{
		//printf("%i|", item->value.Number);
		item = item->previous;
	}
	//printf("hc:, ");
	item = gameState -> Player1Data.HandCards.FirstCard;
	for (int i = 0; i < gameState -> Player1Data.HandCards.CardsCount; i++)
	{
		//printf("%i|", item->value.Number);
		item = item->previous;
	}
	
	//printf(" p2sc: ");
	item = gameState -> Player2Data.StackCards.FirstCard;
	for (int i = 0; i < gameState -> Player2Data.StackCards.CardsCount; i++)
	{
		//printf("%i|", item->value.Number);
		item = item->previous;
	}
	//printf("hc:, ");
	item = gameState -> Player2Data.HandCards.FirstCard;
	for (int i = 0; i < gameState -> Player2Data.HandCards.CardsCount; i++)
	{
		//printf("%i|", item->value.Number);
		item = item->previous;
	}
	//printf(" tc %i\n", gameState -> TurnsCount);
	int player1CardPower = gameState -> Player1Data.StackCards.FirstCard -> value.Number;
	int player2CardPower = gameState -> Player2Data.StackCards.FirstCard -> value.Number;

	item = gameState -> Player1Data.HandCards.FirstCard;

	if (player1CardPower > player2CardPower)
		handleBattleWon(&gameState -> Player1Data, &gameState -> Player2Data, gameState -> GameRules);
	else if (player1CardPower < player2CardPower)
		handleBattleWon(&gameState -> Player2Data, &gameState -> Player1Data, gameState -> GameRules);
	else
		War(gameState);

	handleVictory(gameState);
}

int finishGameIfWarNotPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player2Data;
		return FALSE;
	}
	else if (gameState -> Player2Data.HandCards.CardsCount < CARDS_TAKING_PART_IN_WAR)
	{
		gameState -> Winner = &gameState -> Player1Data;
		return FALSE;
	}

	return TRUE;
}

void initPlayer(PlayerData *playerData)
{
	playerData -> UsedEnemyCardsInWar = 0;
	InitCardsQueue(&playerData -> HandCards);
	InitCardsQueue(&playerData -> StackCards);
}

void InitGame(GameState *gameState, WarOption warOption, int randomSeed)
{
	gameState -> RandomSeed = randomSeed;
	gameState -> TurnsCount = 0;
	gameState -> WarOption = warOption;
	gameState -> Winner = NULL;

	initPlayer(&gameState -> Player1Data);
	initPlayer(&gameState -> Player2Data);
}