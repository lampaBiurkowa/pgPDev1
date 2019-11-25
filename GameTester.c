#include "GameTester.h"
#include "CardsDeliverer.h"
#include "Rank.h"

void InitTestData(TestData *testData, int repeat)
{
	testData -> Repeat = repeat;
	testData -> Player1Rank = 0;
	testData -> Player2Rank = 0;
	testData -> Player1Strategy = RANDOMLY;
	testData -> Player2Strategy = RANDOMLY;
}

void InitStatsHandler(StatsHandler *handler)
{
	handler -> GamesPlayedCount = 0;
	handler -> TurnsTotal = 0;
	handler -> Player1VictoriesCount = 0;
	handler -> Player2VictoriesCount = 0;
}

void playStandardGame(GameState *gameState)
{
	/*if (gameState -> Player1Data.HandCards.CardsCount == 0)
		GiveCards(gameState);*/

	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		Battle(gameState);
		if (gameState -> Winner == &gameState -> Player1Data)
			break;
		else if (gameState -> Winner == &gameState -> Player2Data)
			break;
	}
}

void playSmartGame(GameState *gameState)
{
	/*if (gameState -> Player1Data.HandCards.CardsCount == 0)
		GiveCards(gameState);*/

	int startingPlayerIndex = rand(time(NULL)) % 2;
	PlayerData *startingPlayer;
	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		if (startingPlayerIndex == 0)
			startingPlayer = &gameState -> Player1Data;
		else
			startingPlayer = &gameState -> Player2Data;
		startingPlayerIndex = (startingPlayerIndex + 1) % 2;

		SmartBattle(gameState, startingPlayer);
		if (gameState -> Winner == &gameState -> Player1Data)
			break;
		else if (gameState -> Winner == &gameState -> Player2Data)
			break;
	}
}

int getCardsPerColorFromUser()
{
	const int MIN_CARDS_PER_COLOR = 1;
	const int MAX_CARDS_PER_COLOR = DECK_MAX_SIZE / COLORS_COUNT;

	printf("Podaj rozmiar talii (ilosc kart na kolor: %i - %i)\n", MIN_CARDS_PER_COLOR, MAX_CARDS_PER_COLOR);
	int value;
	while (scanf_s("%i", &value))
		if (value >= MIN_CARDS_PER_COLOR && value <= MAX_CARDS_PER_COLOR)
			return value;
}

WarOption getWarOptionFromUser()
{
	const char A_VARIANT_ID = 'A';
	const char B_VARIANT_ID = 'B';

	char variant;
	printf("Podaj wartiant gry (%c lub %c)\n", A_VARIANT_ID, B_VARIANT_ID);
	while (scanf_s("%c", &variant))
		if (variant == A_VARIANT_ID || variant == B_VARIANT_ID)
			break;

	return variant == A_VARIANT_ID ? WITHOUT_REFILL : WITH_REFILL;
}

void Demonstrate()
{
	GameState gameState;
	InitGame(&gameState, getWarOptionFromUser(), STANDARD, getCardsPerColorFromUser());
	gameState.PrintResults = TRUE;

	TestData testData;
	testData.GameState = gameState;
	testData.Repeat = 1;
	RunTest(&testData);
}

void assignCardsIfNotPreassigned(GameState *gameState, int player1Rank)
{
	if (gameState -> Player1Data.HandCards.CardsCount == 0)
		return;

	if (player1Rank >= GetMinRankForDeckSize(gameState -> CardsPerColor) && player1Rank <= GetMaxRankForDeckSize(gameState -> CardsPerColor)) //TODO  && player2? not hajba ale nwm jak z rank
		GetCardsForRank(gameState, player1Rank);
	else
		GiveCards(gameState);
}

StatsHandler RunTest(TestData *testData)
{
	StatsHandler statsHandler;
	InitStatsHandler(&statsHandler);
	for (int i = 0; i < testData -> Repeat; i++)
	{
		testData -> GameState.RandomSeed = i;
		assignCardsIfNotPreassigned(&testData -> GameState, testData -> Player1Rank);
		if (testData -> GameState.GameRules == STANDARD)
			playStandardGame(&testData -> GameState);
		else
			playSmartGame(&testData -> GameState);

		if (testData -> GameState.Winner == &testData -> GameState.Player1Data)
			statsHandler.Player1VictoriesCount++;
		else if (testData -> GameState.Winner == &testData -> GameState.Player2Data)
			statsHandler.Player2VictoriesCount++;

		statsHandler.TurnsTotal += testData -> GameState.TurnsCount;
		statsHandler.GamesPlayedCount++;
		ResetGame(&testData -> GameState);
	}

	return statsHandler;
}