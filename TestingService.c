#include "TestingService.h"

void simulateGame(WarOption warOption, GameRules gameRules, int cardsPerColor, int repeat, Strategy player1Strategy, Strategy player2Strategy, int player1Rank, int minCardNumberPointing)
{
	TestData testData;
	InitTestData(&testData, repeat);
	testData.Player1Strategy = player1Strategy;
	testData.Player2Strategy = player2Strategy;
	testData.Player1Rank = player1Rank;
	testData.RankMinCardPointingNumber = minCardNumberPointing;
	InitGame(&testData.GameState, warOption, gameRules, cardsPerColor);
	testData.GameState.Player1Data.Strategy = player1Strategy;
	testData.GameState.Player2Data.Strategy = player2Strategy;
	StatsHandler statsHandler = RunTest(&testData);
	printf("Talia %i kart player1: %i player2: %i avg turns: %f\n", testData.GameState.CardsPerColor, statsHandler.Player1VictoriesCount, statsHandler.Player2VictoriesCount, statsHandler.TurnsTotal / (float)statsHandler.GamesPlayedCount);
}

void StandardGameProblem1()
{
	printf("WARIANT A\n");
	for (int i = 5; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, STANDARD, i, 1000, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);
	printf("\nWARIANT B\n");
	for (int i = 5; i <= 13; i++)
		simulateGame(WITH_REFILL, STANDARD, i, 1000, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);
}

void StandardGameProblem2()
{
	printf("\nRANHI REKI - TYLKO STARSZE KARTY\n");
	for (int i = GetMinRankForDeckSize(13, 8); i <= GetMaxRankForDeckSize(13, 8); i++)
	{
		printf("ranha %i: ", i);
		simulateGame(WITHOUT_REFILL, STANDARD, 13, 100, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, i, 8, i);
	}
	printf("\nRANHI REKI - WSZYSTKIE KARTY\n");
	for (int i = GetMinRankForDeckSize(13, MIN_CARD_NUMBER); i <= GetMaxRankForDeckSize(13, MIN_CARD_NUMBER); i++)
	{
		printf("ranha %i: ", i);
		simulateGame(WITHOUT_REFILL, STANDARD, 13, 100, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, i, MIN_CARD_NUMBER, i);
	}
}

void SmartGameProblem1()
{
	printf("\nMADRA WOJNA\n");
	for (int i = 5; i <= 13; i++)
		simulateGame(WITHOUT_REFILL, SMART, i, 1000, SIM_STRATEGY_DEFAULT, SIM_STRATEGY_DEFAULT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);
}

void SmartGameProblem2()
{
	printf("\nLosowa vs Losowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, RANDOMLY, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\nLosowa vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, OFFENSIVE, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\nLosowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, DEFENSIVE, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\nWsciekla vs Wsciekla\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, OFFENSIVE, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\nWsciekla vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, DEFENSIVE, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\nPokojowa vs Pokojowa\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, DEFENSIVE, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);
}

void EfficentStrategy()
{
	printf("\nPokojowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, DEFENSIVE, EFFICENT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\Ofensuwna vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, OFFENSIVE, EFFICENT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);

	printf("\Losowa vs Efektywna\n");
	simulateGame(WITHOUT_REFILL, SMART, 13, 1000, RANDOMLY, EFFICENT, SIM_RANK_DEFAULT, SIM_MIN_CARD_NUM_POINTING);
}