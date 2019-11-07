#pragma once

#include "GameEngine.h"

typedef struct StatsHandler
{
	int GamesPlayedCount;
	int TurnsTotal;
	int Player1VictoriesCount;
	int Player2VictoriesCount;
} StatsHandler;

typedef struct TestData
{
	int Repeat;
	int CardsPerColor;
	GameState GameState;
} TestData;

void InitStatsHandler(StatsHandler *statsHandler);
StatsHandler RunTest(TestData *testData);