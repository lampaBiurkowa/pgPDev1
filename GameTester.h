#pragma once

#include "StandardGameEngine.h"
#include "SmartGameEngine.h"

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

void Demonstrate();
void InitStatsHandler(StatsHandler *statsHandler);
StatsHandler RunTest(TestData *testData);