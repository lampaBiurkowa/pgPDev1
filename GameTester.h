#pragma once

#include "StandardGameEngine.h"

typedef struct StatsHandler
{
	int GamesPlayedCount;
	int TurnsTotal;
	int Player1VictoriesCount;
	int Player2VictoriesCount;
} StatsHandler;

typedef enum GameRules { STANDARD, SMART } GameRules;

typedef struct TestData
{
	int Repeat;
	GameRules GameRules;
	GameState GameState;
} TestData;

void InitStatsHandler(StatsHandler *statsHandler);
StatsHandler RunTest(TestData *testData);