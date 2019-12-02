#include "CardsDeliverer.h"
#include "GameDataPrinter.h"
#include "SmartGameEngine.h"
#include "UserInterface.h"
#include <time.h>

void printChoiceData(CardQueueItem *usersCard,  int startingPlayerIndex)
{
	if (startingPlayerIndex == 1)
		printf("Twoj wybor!\n");
	else
	{
		printf("Karte wybiera przeciwnik, ");
		if (usersCard == NULL)
			printf("ty nie masz kart :)\n");
		else
			printf("ty zagrywasz |%i %s|\n", usersCard -> value.Number, GetCardSuitName(usersCard -> value.Color));
	}
}

void printPreBattleData(GameState *gameState, int startingPlayerIndex)
{
	system("cls");

	printf("Moje karty (od poczatku reki):\n");
	PrintCardsQueue(&gameState -> Player1Data.HandCards);
	printf("Kolejka: %i, ilosc moich kart w rece: %i, ilosc kart przeciwnika w rece: %i.\n\n", gameState -> TurnsCount, gameState -> Player1Data.HandCards.CardsCount, gameState -> Player2Data.HandCards.CardsCount);
	printChoiceData(gameState -> Player1Data.HandCards.FirstCard, startingPlayerIndex);
	printf("> Kliknij dowolny klawisz, aby kontynuowac...\n\n");
	_getch();
}

void startGame(int startingCardNumber)
{
	int cardsPerColor = DECK_MAX_SIZE / COLORS_COUNT - startingCardNumber + MIN_CARD_NUMBER;
	GameState gameState;
	gameState.Player1Data.Strategy = USER;
	gameState.Player2Data.Strategy = RANDOMLY;
	InitGame(&gameState, WITHOUT_REFILL, SMART, cardsPerColor);
	GiveCards(&gameState);
	int startingPlayerIndex = rand(time(NULL)) % 2;
	PlayerData *startingPlayer;
	while (gameState.Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState.Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		if (startingPlayerIndex == 0)
			startingPlayer = &gameState.Player1Data;
		else
			startingPlayer = &gameState.Player2Data;
		
		printPreBattleData(&gameState, startingPlayerIndex);
		SmartBattle(&gameState, startingPlayer);

		if (gameState.Winner == &gameState.Player1Data)
			break;
		else if (gameState.Winner == &gameState.Player2Data)
			break;

		startingPlayerIndex = (startingPlayerIndex + 1) % 2;
	}
}

void printEntryText()
{
	system("cls");
	printf("     === W o j n a ===\n");
	printf("       gra karciana\n\n\n");
}

int playerWantsToPlay()
{
	const char EXIT_CHAR = 'X';
	const char START_KEY = 'Z';
	char choice;
	while (scanf_s("%c", &choice))
	{
		if (choice == EXIT_CHAR)
			return FALSE;
		if (choice == START_KEY)
			return TRUE;
		else
			printf("> Podaj poprawny znak (X lub Z)\n");
	}

	return FALSE;
}

int getStartingCardNumber()
{
	int startingCardNumber;
	while (scanf_s("%i", &startingCardNumber))
		if (startingCardNumber >= MIN_CARD_NUMBER && startingCardNumber <= MAX_CARD_NUMBER)
			break;
		else
			printf("> Podaj liczbe z zakresu %i - %i wlacznie\n", MIN_CARD_NUMBER, MAX_CARD_NUMBER);

	return startingCardNumber;
}

void PlayWithComputer()
{
	printEntryText();
	printf("> Podaj X aby wyjsc, Z, aby rozpoczac\n");
	if (!playerWantsToPlay())
		return;

	printf("> Podaj rozmiar talii (wpisz minimalny numer kart, ktore beda w talii (od %i do %i))?\n", MIN_CARD_NUMBER, MAX_CARD_NUMBER);
	startGame(getStartingCardNumber());
}