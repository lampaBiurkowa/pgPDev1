#pragma once

#include "StandardGameEngine.h"

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
	GameState GameState;
	Strategy Player1Strategy;
	Strategy Player2Strategy;
} TestData;

void InitStatsHandler(StatsHandler *statsHandler);
StatsHandler RunTest(TestData *testData);