#include <stdio.h>
#include "GameEngine.h"
#include "GameTester.h"
#include "InputReader.h"
#include "Structures.h"
#include "Rank.h"
#include "CardsDeliverer.h"

int main()
{
	GameState test;
	test.CardsPerColor = 13;
	test.RandomSeed = 123;
	test.WarOption = WITHOUT_REFILL;
	InitGame(&test);
	GetCardsForRank(0, &test);
	
	CardQueueItem *item = test.Player1Data.HandCards.FirstCard;
	for (int i = 0; i < test.Player1Data.HandCards.CardsCount; i++)
	{
		printf("| %i %i ", item -> value.Color, item->value.Number);
		item = item->previous;
	}

	printf("\ndfsdfa %i ", test.Player1Data.HandCards.CardsCount);
	//ReadGameState("teest.txt");
	TestData testData;
	testData.Repeat = 1000;
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.CardsPerColor = i;
		gameState.WarOption = WITHOUT_REFILL;
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("%i %i %f\n", statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}
	printf("\n\n");
	for (int i = 8; i <= 13; i++)
	{
		GameState gameState;
		gameState.CardsPerColor = i;
		gameState.WarOption = WITH_REFILL;
		testData.GameState = gameState;
		StatsHandler statsHandler = RunTest(&testData);
		printf("%i %i %f\n", statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
	}

	return 0;
}