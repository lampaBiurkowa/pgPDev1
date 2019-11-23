#include <stdio.h>
#include "StandardGameEngine.h"
#include "SmartGameEngine.h"
#include "GameTester.h"
#include "InputHandler.h"
#include "Structures.h"
#include "Rank.h"
#include "CardsDeliverer.h"
#include "UserInterface.h"

void simulateGame(WarOption warOption, GameRules gameRules, int cardsPerColor, int repeat, Strategy player1Strategy, Strategy player2Strategy)
{
	TestData testData;
	testData.Repeat = repeat;
	testData.Player1Strategy = player1Strategy;
	testData.Player2Strategy = player2Strategy;
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
	printf("\nZ PLIKU\n");
	simulateGameFromFile("teest.txt", WITHOUT_REFILL, STANDARD, 13, 1, RANDOMLY, RANDOMLY);
}

void standardGameProblem1()
{
	printf("WARIANT A\n");
	for (int i = 8; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, STANDARD, i, 1000, RANDOMLY, RANDOMLY);
	printf("\nWARIANT B\n");
	for (int i = 8; i <= 13; i++)
		simulateGame(WITH_REFILL, STANDARD, i, 1000, RANDOMLY, RANDOMLY);
}

void smartGameProblem1()
{
	printf("\nMADRA WOJNA\n");
	for (int i = 8; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, SMART, i, 1000, RANDOMLY, RANDOMLY);
}

void smartGameProblem2()
{
	printf("\nLosowa vs Losowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, RANDOMLY);

	printf("\nLosowa vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, OFFENSIVE);

	printf("\nLosowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, DEFENSIVE);

	printf("\nWsciekla vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, OFFENSIVE);

	printf("\nWsciekla vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, DEFENSIVE);

	printf("\nPokojowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, DEFENSIVE);
}

void efficentStrategy()
{
	printf("\nPokojowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, EFFICENT);

	printf("\Ofensuwna vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, EFFICENT);

	printf("\Losowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, EFFICENT);
}

int main()
{
	int choice;
	while (1)
	{
		printf("Wybierz:\n");
		printf("1 - pokazac wyniki problemu 1 gry w zwykla wojne\n");
		printf("2 - zademonstrowac zwykla wojne\n");
		printf("3 - pokazac wyniki problemu 1 gry w madra wojne\n");
		printf("4 - pokazac wyniki problemu 2 gry w madra wojne\n");
		printf("5 - zagrac z komputerem w zwykla wojne\n");
		printf("6 - pokazac wyniki strategii gry w madra wojne na dodatkowe punkty\n");
		printf("7 - zesrac sie\n");
		printf("8 - pokazac wyniki gier z plikow\n");

		while (scanf_s("%i", &choice))
		{
			switch (choice)
			{
			case 1:
				standardGameProblem1();
				break;
			case 2:
				Demonstrate();
				break;
			case 3:
				smartGameProblem1();
				break;
			case 4:
				smartGameProblem2();
				break;
			case 5:
				ShowEntryScreen();
				break;
			case 6:
				efficentStrategy();
				break;
			case 7:
				printf("jea\n");
				break;
			case 8:
				playFromFile();
				break;
			}
		}
	}
	WriteInputData("howno.txt", 13, 0);

	return 0;
}