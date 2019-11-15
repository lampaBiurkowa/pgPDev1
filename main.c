#include <stdio.h>
#include "StandardGameEngine.h"
#include "SmartGameEngine.h"
#include "GameTester.h"
#include "InputReader.h"
#include "Structures.h"
#include "Rank.h"
#include "CardsDeliverer.h"

int main()
{
	GameState test;
	test.CardsPerColor = 13;
	InitGame(&test, WITHOUT_REFILL, 123);
	GetCardsForRank(0, &test);

	printf("WARIANT A\n");
	TestData testData;
	testData.Repeat = 1000;
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.CardsPerColor = i;
		gameState.WarOption = WITHOUT_REFILL;
		gameState.GameRules = STANDARD;
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", i * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	printf("WARIANT B\n\n");
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.CardsPerColor = i;
		gameState.WarOption = WITH_REFILL;
		gameState.GameRules = STANDARD;
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", i * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	printf("MADRA WOJNA\n\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = RANDOMLY;
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.CardsPerColor = i;
		gameState.WarOption = WITHOUT_REFILL;
		gameState.GameRules = SMART;
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", i * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}

	printf("Losowa vs Losowa\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = RANDOMLY;
	GameState gameState;
	gameState.CardsPerColor = 13;
	gameState.WarOption = WITHOUT_REFILL;
	gameState.GameRules = SMART;
	testData.GameState = gameState;
	StatsHandler statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);


	printf("Losowa vs Wsciekla\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = OFFENSIVE;
	gameState.CardsPerColor = 13;
	gameState.WarOption = WITHOUT_REFILL;
	gameState.GameRules = SMART;
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("Losowa vs Pokojowa\n\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = DEFENSIVE;
	//GameState gameState;
	gameState.CardsPerColor = 13;
	gameState.WarOption = WITHOUT_REFILL;
	gameState.GameRules = SMART;
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("Wsciekla vs Wsciekla\n");
	testData.Player1Strategy = OFFENSIVE;
	testData.Player2Strategy = OFFENSIVE;
	//GameState gameState;
	gameState.CardsPerColor = 13;
	gameState.WarOption = WITHOUT_REFILL;
	gameState.GameRules = SMART;
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("Wsciekla vs Pokojowa\n");
	testData.Player1Strategy = OFFENSIVE;
	testData.Player2Strategy = DEFENSIVE;
	//GameState gameState;
	gameState.CardsPerColor = 13;
	gameState.WarOption = WITHOUT_REFILL;
	gameState.GameRules = SMART;
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("Pokojowa vs Pokojowa\n");
	testData.Player1Strategy = DEFENSIVE;
	testData.Player2Strategy = DEFENSIVE;
	//GameState gameState;
	gameState.CardsPerColor = 13;
	gameState.WarOption = WITHOUT_REFILL;
	gameState.GameRules = SMART;
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	return 0;
}