#pragma once

#include "SmartGameEngine.h"
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
	GameState GameState;
	int Player1Rank;
	int RankMinCardPointingNumber;
	Strategy Player1Strategy;
	Strategy Player2Strategy;
	int Repeat;
} TestData;

void Demonstrate();
void InitStatsHandler(StatsHandler *statsHandler);
void InitTestData(TestData *testData, int repeat);
StatsHandler RunTest(TestData *testData);