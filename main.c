#include <stdio.h>
#include "StandardGameEngine.h"
#include "SmartGameEngine.h"
#include "GameTester.h"
#include "InputReader.h"
#include "Structures.h"
#include "Rank.h"
#include "CardsDeliverer.h"
#include "UserInterface.h"

int main()
{/*
	TestData testData;
	testData.Repeat = 1000;

	printf("WARIANT A\n");
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		InitGame(&gameState, WITHOUT_REFILL, STANDARD, i);
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", i * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	printf("\nWARIANT B\n");
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		InitGame(&gameState, WITH_REFILL, STANDARD, i);
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", i * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	printf("\nMADRA WOJNA\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = RANDOMLY;
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		InitGame(&gameState, WITHOUT_REFILL, SMART, i);
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", i * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	
	printf("\nLosowa vs Losowa\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = RANDOMLY;
	GameState gameState;
	InitGame(&gameState, WITHOUT_REFILL, SMART, 13);
	testData.GameState = gameState;
	StatsHandler statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	
	printf("\nLosowa vs Wsciekla\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = OFFENSIVE;
	InitGame(&gameState, WITHOUT_REFILL, SMART, 13);
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("\nLosowa vs Pokojowa\n");
	testData.Player1Strategy = RANDOMLY;
	testData.Player2Strategy = DEFENSIVE;
	InitGame(&gameState, WITHOUT_REFILL, SMART, 13);
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("\nWsciekla vs Wsciekla\n");
	testData.Player1Strategy = OFFENSIVE;
	testData.Player2Strategy = OFFENSIVE;
	InitGame(&gameState, WITHOUT_REFILL, SMART, 13);
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("\nWsciekla vs Pokojowa\n");
	testData.Player1Strategy = OFFENSIVE;
	testData.Player2Strategy = DEFENSIVE;
	InitGame(&gameState, WITHOUT_REFILL, SMART, 13);
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);

	printf("\nPokojowa vs Pokojowa\n");
	testData.Player1Strategy = DEFENSIVE;
	testData.Player2Strategy = DEFENSIVE;
	InitGame(&gameState, WITHOUT_REFILL, SMART, 13);
	testData.GameState = gameState;
	statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", 13 * COLORS_COUNT, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	*/
	ShowEntryScreen();

	return 0;
}