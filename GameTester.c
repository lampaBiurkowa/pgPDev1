#include "GameTester.h"
#include "CardsDeliverer.h"
#include "Rank.h"

void InitTestData(TestData *testData, int repeat)
{
	testData -> RandomSeed = 0;
	testData -> Repeat = repeat;
	testData -> Player1Rank = 0;
	testData -> RankMinCardPointingNumber = MIN_CARD_NUMBER;
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
	const int GAME_LOOPED_INDICATOR = 10000;

	while (gameState -> Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState -> Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		Battle(gameState);

		if (gameState -> TurnsCount > GAME_LOOPED_INDICATOR) //zapobiega loopowaniu sie gry na malych taliach
			break;

		if (gameState -> Winner == &gameState -> Player1Data)
			break;
		else if (gameState -> Winner == &gameState -> Player2Data)
			break;
	}
}

void playSmartGame(GameState *gameState)
{
	int startingPlayerIndex = rand() % 2;
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

void assignCardsIfNotPreassigned(GameState *gameState, int player1Rank, int minCardNumberPointing)
{
	if (gameState -> Player1Data.HandCards.CardsCount != 0)
		return;

	int rankNotToSmall = player1Rank >= GetMinRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing);
	int rankNotToBig = player1Rank <= GetMaxRankForDeckSize(gameState -> CardsPerColor, minCardNumberPointing);
	if (rankNotToSmall && rankNotToBig)
	{
		GetCardsForRank(gameState, player1Rank, minCardNumberPointing);
		/*printf("dsafdsaf %i %i ",player1Rank, GetPlayerRank(&gameState -> Player1Data, minCardNumberPointing));
		printf("dsafdsaf %i\n", GetPlayerRank(&gameState -> Player2Data, minCardNumberPointing));
		PrintCardsQueue(&gameState -> Player1Data.HandCards);
		PrintCardsQueue(&gameState -> Player2Data.HandCards);*/
	}
	else
		GiveCards(gameState);
}

StatsHandler RunTest(TestData *testData)
{
	StatsHandler statsHandler;
	InitStatsHandler(&statsHandler);
	for (int i = 0; i < testData -> Repeat; i++)
	{
		testData -> GameState.RandomSeed = i + testData -> RandomSeed;
		assignCardsIfNotPreassigned(&testData -> GameState, testData -> Player1Rank, testData -> RankMinCardPointingNumber);
		if (testData -> GameState.GameRules == STANDARD)
			playStandardGame(&testData -> GameState);
		else
			playSmartGame(&testData -> GameState);

		if (testData -> GameState.Winner == &testData -> GameState.Player1Data)
			statsHandler.Player1VictoriesCount++;
		else if (testData -> GameState.Winner == &testData -> GameState.Player2Data)
			statsHandler.Player2VictoriesCount++;
		else
			i--;

		if (testData -> GameState.PrintResults)
			PrintVictoryInfo(&testData -> GameState);

		statsHandler.TurnsTotal += testData -> GameState.TurnsCount;
		statsHandler.GamesPlayedCount++;
		ResetGame(&testData -> GameState);
	}

	return statsHandler;
}