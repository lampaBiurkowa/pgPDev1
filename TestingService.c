#include "TestingService.h"

void simulateGame(WarOption warOption, GameRules gameRules, int cardsPerColor, int repeat, Strategy player1Strategy, Strategy player2Strategy, int player1Rank, int minCardNumberPointing, int testRandomSeed)
{
	TestData testData;
	InitTestData(&testData, repeat);
	testData.Player1Strategy = player1Strategy;
	testData.Player2Strategy = player2Strategy;
	testData.Player1Rank = player1Rank;
	testData.RankMinCardPointingNumber = minCardNumberPointing;
	testData.RandomSeed = testRandomSeed;
	InitGame(&testData.GameState, warOption, gameRules, cardsPerColor);
	StatsHandler statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", testData.GameState.CardsPerColor, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
}

void StandardGameProblem1()
{
	printf("WARIANT A\n");
	for (int i = 5; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, STANDARD, i, 1000, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);
	printf("\nWARIANT B\n");
	for (int i = 5; i <= 13; i++)
		simulateGame(WITH_REFILL, STANDARD, i, 1000, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);
}

void StandardGameProblem2()
{
	printf("\nRANHI REKI - TYLKO STARSZE KARTY\n");
	for (int i = GetMinRankForDeckSize(13, 8); i <= GetMaxRankForDeckSize(13, 8); i++)
	{
		printf("ranha %i: ", i);
		simulateGame(WITHOUT_REFILL, SMART, 13, 100, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, i, 8, i);
	}
	printf("\nRANHI REKI - WSZYSTKIE KARTY\n");
	for (int i = GetMinRankForDeckSize(13, MIN_CARD_NUMBER); i <= GetMaxRankForDeckSize(13, MIN_CARD_NUMBER); i++)
	{
		printf("ranha %i: ", i);
		simulateGame(WITHOUT_REFILL, SMART, 13, 100, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, i, MIN_CARD_NUMBER, i);
	}
}

void SmartGameProblem1()
{
	printf("\nMADRA WOJNA\n");
	for (int i = 5; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, SMART, i, 1000, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);
}

void SmartGameProblem2()
{
	//int rank = GetMaxRankForDeckSize(13 * COLORS_COUNT, 3) / 2;
	int rank = 0;
	printf("\nLosowa vs Losowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, RANDOMLY, rank, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\nLosowa vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, OFFENSIVE, rank, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\nLosowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, DEFENSIVE, rank, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\nWsciekla vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, OFFENSIVE, rank, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\nWsciekla vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, DEFENSIVE, rank, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\nPokojowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, DEFENSIVE, rank, 3, SIM_SEED_DEFAULT);
}

void EfficentStrategy()
{
	printf("\nPokojowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, EFFICENT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\Ofensuwna vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, EFFICENT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);

	printf("\Losowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, EFFICENT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);
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

void PlayFromFile()
{
	char path[16] = "syf/hownoXX.txt";
	printf("\nZ PLIKU\n");
	for (int i = 0; i < 100; i++)
	{
		path[9] = ((int)'0' + i / 10);
		path[10] = ((int)'0' + i % 10);
		simulateGameFromFile(path, WITHOUT_REFILL, STANDARD, 13, 1, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_MIN_CARD_NUM_POINTING, SIM_SEED_DEFAULT);
	}
}