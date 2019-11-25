#include <stdio.h>
#include "StandardGameEngine.h"
#include "SmartGameEngine.h"
#include "GameTester.h"
#include "InputHandler.h"
#include "Structures.h"
#include "Rank.h"
#include "CardsDeliverer.h"
#include "UserInterface.h"

void simulateGame(WarOption warOption, GameRules gameRules, int cardsPerColor, int repeat, Strategy player1Strategy, Strategy player2Strategy, int player1Rank, int player2Rank)
{
	TestData testData;
	InitTestData(&testData, repeat);
	testData.Player1Strategy = player1Strategy;
	testData.Player2Strategy = player2Strategy;
	testData.Player1Rank = player1Rank;
	testData.Player2Rank = player2Rank;
	InitGame(&testData.GameState, warOption, gameRules, cardsPerColor);
	StatsHandler statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", testData.GameState.CardsPerColor, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
}

void simulateGameFromFile(const char *fileName, WarOption warOption, GameRules gameRules, int cardsPerColor, int repeat, Strategy player1Strategy, Strategy player2Strategy)
{
	TestData testData;
	testData.Repeat = repeat;
	testData.Player1Strategy = player1Strategy;
	testData.Player2Strategy = player2Strategy;
	InitGameFromFile(&testData.GameState, fileName, warOption, gameRules);
	StatsHandler statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", testData.GameState.CardsPerColor, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
}

void playFromFile()
{
	char path[16] = "syf/hownoXX.txt";
	printf("\nZ PLIKU\n");
	for (int i = 0; i < 100; i++)
	{
		path[9] = ((int)'0' + i / 10);
		path[10] = ((int)'0' + i % 10);
		simulateGameFromFile(path, WITHOUT_REFILL, STANDARD, 13, 1, RANDOMLY, RANDOMLY, 0, 0);
	}
}

void standardGameProblem1()
{
	printf("WARIANT A\n");
	for (int i = 8; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, STANDARD, i, 1000, RANDOMLY, RANDOMLY, 0, 0);
	printf("\nWARIANT B\n");
	for (int i = 8; i <= 13; i++)
		simulateGame(WITH_REFILL, STANDARD, i, 1000, RANDOMLY, RANDOMLY, 0, 0);
}

void smartGameProblem1()
{
	printf("\nMADRA WOJNA\n");
	for (int i = 8; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, SMART, i, 1000, RANDOMLY, RANDOMLY, 0, 0);
}

void standardGameProblem2()
{
	printf("\nRANHI REKI\n");
	for (int i = GetMinRankForDeckSize(13); i <= GetMaxRankForDeckSize(13); i++)
	{
		printf("ranha %i: ", i);
		simulateGame(WITHOUT_REFILL, SMART, 13, 100, RANDOMLY, RANDOMLY, i, 0);
	}
}

void smartGameProblem2()
{
	printf("\nLosowa vs Losowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, RANDOMLY, 0, 0);

	printf("\nLosowa vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, OFFENSIVE, 0, 0);

	printf("\nLosowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, DEFENSIVE, 0, 0);

	printf("\nWsciekla vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, OFFENSIVE, 0, 0);

	printf("\nWsciekla vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, DEFENSIVE, 0, 0);

	printf("\nPokojowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, DEFENSIVE, 0, 0);
}

void efficentStrategy()
{
	printf("\nPokojowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, EFFICENT, 0, 0);

	printf("\Ofensuwna vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, EFFICENT, 0, 0);

	printf("\Losowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, EFFICENT, 0, 0);
}

void generateTestFiles()
{
	char path[16] = "syf/hownoXX.txt";
	for (int i = 0; i < 100; i++)
	{
		path[9] = ((int)'0' + i / 10);
		path[10] = ((int)'0' + i % 10);
		WriteInputData(path, 13, i);
	}
}

int main()
{
	int choice;
	while (1)
	{
		printf("Wybierz:\n");
		printf("1 - pokazac wyniki problemu 1 gry w zwykla wojne\n");
		printf("2 - pokazac wyniki problemu 2 gry w zwykla wojne\n");
		printf("3 - zademonstrowac zwykla wojne\n");
		printf("4 - pokazac wyniki problemu 1 gry w madra wojne\n");
		printf("5 - pokazac wyniki problemu 2 gry w madra wojne\n");
		printf("6 - zagrac z komputerem w zwykla wojne\n");
		printf("7 - pokazac wyniki strategii gry w madra wojne na dodatkowe punkty\n");
		printf("8 - pokazac wyniki gier z plikow\n");

		while (scanf_s("%i", &choice))
		{
			switch (choice)
			{
			case 1:
				standardGameProblem1();
				break;
			case 2:
				standardGameProblem2();
				break;
			case 3:
				Demonstrate();
				break;
			case 4:
				smartGameProblem1();
				break;
			case 5:
				smartGameProblem2();
				break;
			case 6:
				ShowEntryScreen();
				break;
			case 7:
				efficentStrategy();
				break;
			case 8:
				playFromFile();
				break;
			}
		}
	}

	return 0;
}