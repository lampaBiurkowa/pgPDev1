#include "UserInterface.h"
#include "SmartGameEngine.h"
#include <time.h>

void startGame()
{
	GameState gameState;
	const int DEFAULT_SEED = 0;
	InitGame(&gameState, WITHOUT_REFILL, 0); //tylko jedna gra wiêc nie potrzeba dodatkowego parametru do ziarna
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
	while (choice = getch())
	{
		if (choice == EXIT_CHAR)
			return;
		if (choice == START_KEY)
			break;
	}

	startGame();
}