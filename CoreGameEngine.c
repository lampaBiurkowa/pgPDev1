#include "CardsDeliverer.h"
#include "CoreGameEngine.h"
#include "GameDataPrinter.h"
#include "InputHandler.h"

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

	int player1CardPower = gameState -> Player1Data.StackCards.FirstCard -> value.Number;
	int player2CardPower = gameState -> Player2Data.StackCards.FirstCard -> value.Number;

	if (gameState -> PrintResults)
		PrintStandardTurnData(gameState);

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

void InitGame(GameState *gameState, WarOption warOption, GameRules gameRules, int cardsPerColor)
{
	const int DEFAULT_SEED = 0;

	gameState -> CardsPerColor = cardsPerColor;
	gameState -> GameRules = gameRules;
	gameState -> PrintResults = FALSE;
	gameState -> RandomSeed = DEFAULT_SEED;
	gameState -> TurnsCount = 0;
	gameState -> WarOption = warOption;
	gameState -> Winner = NULL;

	initPlayer(&gameState -> Player1Data);
	initPlayer(&gameState -> Player2Data);
}

void ResetGame(GameState *gameState)
{
	gameState -> TurnsCount = 0;
	gameState -> Winner = NULL;

	initPlayer(&gameState -> Player1Data);
	initPlayer(&gameState -> Player2Data);
}

void InitGameFromFile(GameState *gameState, const char *path, WarOption warOption, GameRules gameRules)
{
	const int DEFAULT_SEED = 0;

	int *cardNumbers = (int *)malloc(DECK_MAX_SIZE * sizeof(int));
	int cardsCount = GetCardNumbersFromFile(path, cardNumbers);

	gameState -> CardsPerColor = cardsCount / COLORS_COUNT;
	gameState -> GameRules = gameRules;
	gameState -> PrintResults = FALSE;
	gameState -> RandomSeed = DEFAULT_SEED;
	gameState -> TurnsCount = 0;
	gameState -> WarOption = warOption;
	gameState -> Winner = NULL;

	initPlayer(&gameState -> Player1Data);
	initPlayer(&gameState -> Player2Data);
	AssignCardNumbersFromArray(gameState, cardNumbers, cardsCount);
}

void AppendStacksInWar(GameState *gameState)
{
	for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
	{
		AddFirstCardToStack(&gameState -> Player1Data);
		AddFirstCardToStack(&gameState -> Player2Data);

		gameState -> TurnsCount++;

		if (gameState -> PrintResults && i != CARDS_TAKING_PART_IN_WAR - 1) // prevents from duplicating turn data info for user
			PrintWarCausingTurnData(gameState);
	}
}

int performWarOptionWithoutRefillIfPossible(GameState *gameState)
{
	if (!finishGameIfWarNotPossible(gameState))
		return FALSE;

	AppendStacksInWar(gameState);

	return TRUE;
}

void addCardToStackWithHelp(PlayerData *helpingPlayer, PlayerData *playerNeedingHelp)
{
	Card card = PopFrontCard(&helpingPlayer -> HandCards);
	PushFrontCard(&playerNeedingHelp -> StackCards, card);
}

void buildStackWithHelp(PlayerData *helpingPlayer, PlayerData *playerNeedingHelp, GameState *gameState)
{
	int playerNeedingHelpCardsCountBeforeWar = playerNeedingHelp -> HandCards.CardsCount;
	if (playerNeedingHelpCardsCountBeforeWar == 1)
	{
		AddFirstCardToStack(playerNeedingHelp);
		AddFirstCardToStack(helpingPlayer);
		gameState -> TurnsCount++;

		if (gameState -> PrintResults)
			PrintStandardTurnData(gameState);

		gameState -> TurnsCount++;

		if (gameState -> PrintResults)
			PrintWarWithSmallRefillTurnData(gameState, helpingPlayer);

		addCardToStackWithHelp(helpingPlayer, playerNeedingHelp);
		AddFirstCardToStack(helpingPlayer);
	}
	else
	{
		gameState -> TurnsCount++;

		if (gameState -> PrintResults)
			PrintFirstPartWarWithBigRefillTurnData(gameState, helpingPlayer);

		for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
			addCardToStackWithHelp(helpingPlayer, playerNeedingHelp);

		gameState -> TurnsCount++;

		if (gameState -> PrintResults)
			PrintSecondPartWarWithBigRefillTurnData(gameState, helpingPlayer);

		for (int i = 0; i < CARDS_TAKING_PART_IN_WAR; i++)
			AddFirstCardToStack(helpingPlayer);
	}

	playerNeedingHelp -> UsedEnemyCardsInWar = TRUE;
}

int performWarOptionWithRefillIfPossible(GameState *gameState)
{
	if (gameState -> Player1Data.HandCards.CardsCount < 2 || gameState -> Player2Data.HandCards.CardsCount < 2)
	{
		if (gameState -> Player1Data.HandCards.CardsCount == 1 && gameState -> Player2Data.HandCards.CardsCount < 3)
			return FALSE;
		if (gameState -> Player1Data.HandCards.CardsCount == 0 && gameState -> Player2Data.HandCards.CardsCount < 4)
			return FALSE;
		if (gameState -> Player2Data.HandCards.CardsCount == 1 && gameState -> Player1Data.HandCards.CardsCount < 3)
			return FALSE;
		if (gameState -> Player2Data.HandCards.CardsCount == 0 && gameState -> Player1Data.HandCards.CardsCount < 4)
			return FALSE;

		if (gameState -> Player1Data.HandCards.CardsCount < 2 && !gameState -> Player1Data.UsedEnemyCardsInWar)
			buildStackWithHelp(&gameState -> Player2Data, &gameState -> Player1Data, gameState);
		else if (gameState -> Player2Data.HandCards.CardsCount < 2 && !gameState -> Player2Data.UsedEnemyCardsInWar)
			buildStackWithHelp(&gameState -> Player1Data, &gameState -> Player2Data, gameState);
		else
			return FALSE;
	}
	else
		AppendStacksInWar(gameState);

	return TRUE;
}

void War(GameState *gameState)
{
	if (gameState -> WarOption == WITHOUT_REFILL)
	{
		if (performWarOptionWithoutRefillIfPossible(gameState))
			HandleComparingCards(gameState);
	}
	else if (gameState -> WarOption == WITH_REFILL)
	{
		if (performWarOptionWithRefillIfPossible(gameState))
			HandleComparingCards(gameState);
	}
}