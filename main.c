#include <stdio.h>
#include "GameEngine.h"
#include "GameTester.h"
#include "Structures.h"


int main()
{
	TestData testData;
	testData.Repeat = 1000;
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.WarOption = WITHOUT_REFILL;
		testData.GameState = gameState;
		testData.CardsPerColor = i;
		StatsHandler statsHandler = RunTest(&testData);
		printf("%i %i %f\n", statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	printf("\n\n");
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.WarOption = WITH_REFILL;
		testData.GameState = gameState;
		testData.CardsPerColor = i;
		StatsHandler statsHandler = RunTest(&testData);
		printf("%i %i %f\n", statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}

	return 0;
}