#include "CardsDeliverer.h"
#include "GameDataPrinter.h"
#include "SmartGameEngine.h"
#include "UserInterface.h"
#include <time.h>


void showPreBattleData(GameState *gameState)
{
	system("cls");

	printf("Moje karty (od poczatku reki):\n");
	PrintCardsQueue(&gameState -> Player1Data.HandCards);
	printf("Kolejka: %i, ilosc moich kart w rece: %i, ilosc kart przeciwnika w rece: %i. Kliknij dowolny klawisz, aby kontynuowac...\n", gameState -> TurnsCount, gameState -> Player1Data.HandCards.CardsCount, gameState -> Player2Data.HandCards.CardsCount);
	_getch();
}

void startGame(int startingCardNumber)
{
	int cardsPerColor = DECK_MAX_SIZE / COLORS_COUNT - startingCardNumber + MIN_CARD_NUMBER;
	GameState gameState;
	gameState.Player1Data.Strategy = USER;
	gameState.Player2Data.Strategy = RANDOMLY;
	InitGame(&gameState, WITHOUT_REFILL, SMART, cardsPerColor); //tylko jedna gra wiêc nie potrzeba dodatkowego parametru do ziarna
	GiveCards(&gameState);
	int startingPlayerIndex = rand(time(NULL)) % 2;
	PlayerData *startingPlayer;
	while (gameState.Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState.Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		if (startingPlayerIndex == 0)
			startingPlayer = &gameState.Player1Data;
		else
			startingPlayer = &gameState.Player2Data;
		startingPlayerIndex = (startingPlayerIndex + 1) % 2;

		showPreBattleData(&gameState, &gameState.Player1Data);
		SmartBattle(&gameState, startingPlayer);
		if (gameState.Winner == &gameState.Player1Data)
			break;
		else if (gameState.Winner == &gameState.Player2Data)
			break;
	}
}

void ShowEntryScreen()
{
	const char EXIT_CHAR = 'X';
	const char START_KEY = 'Z';
	system("cls");
	printf("wojna hra karciana jea\n");
	printf("podaj X aby wyjsc, Z, aby rozpoczasc");
	char choice;
	while (choice = _getch())
	{
		if (choice == EXIT_CHAR)
			return;
		if (choice == START_KEY)
			break;
	}

	system("cls");
	printf("Podaj rozmiar talii (wpisz minimalny numer kart, ktore beda w talii (od 2 do 7)?");
	int cardsPerColor;
	int twoNumASCIICode = (int)'2';
	int sevenNumASCIICode = (int)'7';
	while (cardsPerColor = (int)_getch())
		if (cardsPerColor >= twoNumASCIICode && cardsPerColor <= sevenNumASCIICode)
			break;

	startGame(cardsPerColor - twoNumASCIICode + MIN_CARD_NUMBER);
}