#include "UserInterface.h"
#include "CardsDeliverer.h"
#include <time.h>

void startGame(int startingCardNumber)
{
	int cardsPerColor = DECK_MAX_SIZE / COLORS_COUNT - startingCardNumber + MIN_CARD_NUMBER;
	GameState gameState;
	const int DEFAULT_SEED = 0;
	InitGame(&gameState, WITHOUT_REFILL, cardsPerColor, 0); //tylko jedna gra wiêc nie potrzeba dodatkowego parametru do ziarna
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

	printf("Podaj rozmiar talii (wpisz minimalny numer kart, ktore beda w talii (od 2 do 7)?");
	int cardsPerColor;
	int twoNumASCIICode = (int)'2';
	int sevenNumASCIICode = (int)'7';
	while (cardsPerColor = (int)_getch())
		if (cardsPerColor >= twoNumASCIICode && cardsPerColor <= sevenNumASCIICode)
			break;

	startGame(cardsPerColor);
}