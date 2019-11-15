#include "GameTester.h"
#include "CardsDeliverer.h"

void InitStatsHandler(StatsHandler *handler)
{
	handler -> GamesPlayedCount = 0;
	handler -> TurnsTotal = 0;
	handler -> Player1VictoriesCount = 0;
	handler -> Player2VictoriesCount = 0;
}

void playStandardGame(int deckSize, WarOption warOption, GameState *gameState, int seed)
{
	InitGame(gameState, warOption, seed);
	GiveCards(gameState);
	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		Battle(gameState);
		if (gameState -> Winner == &gameState -> Player1Data)
			break;
		else if (gameState -> Winner == &gameState -> Player2Data)
			break;
	}
}

void playSmartGame(int deckSize, WarOption warOption, GameState *gameState, int seed)
{
	InitGame(gameState, warOption, seed);
	GiveCards(gameState);
	int startingPlayerIndex = 0;
	PlayerData *startingPlayer;
	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		if (startingPlayerIndex == 0)
			startingPlayer = &gameState -> Player1Data;
		else
			startingPlayer = &gameState -> Player2Data;
		startingPlayer = (startingPlayerIndex + 1) % 2;

		SmartBattle(gameState, startingPlayer);
		if (gameState -> Winner == &gameState -> Player1Data)
			break;
		else if (gameState -> Winner == &gameState -> Player2Data)
			break;
	}
}

StatsHandler RunTest(TestData *testData)
{
	StatsHandler statsHandler;
	InitStatsHandler(&statsHandler);
	for (int i = 0; i < 1000; i++)
	{
		if (testData -> GameState.GameRules == STANDARD)
			playStandardGame(testData -> GameState.CardsPerColor, testData -> GameState.WarOption, &testData -> GameState, i);
		else
			playSmartGame(testData -> GameState.CardsPerColor, testData -> GameState.WarOption, &testData -> GameState, i);

		if (testData -> GameState.Winner == &testData -> GameState.Player1Data)
			statsHandler.Player1VictoriesCount++;
		else if (testData -> GameState.Winner == &testData -> GameState.Player2Data)
			statsHandler.Player2VictoriesCount++;

		statsHandler.TurnsTotal += testData -> GameState.TurnsCount;
		statsHandler.GamesPlayedCount++;
	}

	return statsHandler;
}