#include "GameTester.h"

void InitStatsHandler(StatsHandler *handler)
{
	handler -> GamesPlayedCount = 0;
	handler -> TurnsTotal = 0;
	handler -> Player1VictoriesCount = 0;
	handler -> Player2VictoriesCount = 0;
}

void playGame(int deckSize, WarOption warOption, GameState *gameState, int seed)
{
	gameState -> WarOption = warOption;
	gameState -> RandomSeed = seed;
	InitGame(gameState);
	GiveCards(deckSize, gameState);
	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		Battle(gameState);
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
		playGame(testData -> CardsPerColor, testData -> GameState.WarOption, &testData -> GameState, i);
		if (testData -> GameState.Winner == &testData -> GameState.Player1Data)
			statsHandler.Player1VictoriesCount++;
		else if (testData -> GameState.Winner == &testData -> GameState.Player2Data)
			statsHandler.Player2VictoriesCount++;

		statsHandler.TurnsTotal += testData -> GameState.TurnsCount;
		statsHandler.GamesPlayedCount++;
	}

	return statsHandler;
}