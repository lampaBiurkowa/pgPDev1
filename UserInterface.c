#include "CardsDeliverer.h"
#include "SmartGameEngine.h"
#include "UserInterface.h"
#include "UserInterfaceDataPrinter.h"
#include <time.h>

void startGame(int startingCardNumber)
{
	int cardsPerColor = DECK_MAX_SIZE / COLORS_COUNT - startingCardNumber + MIN_CARD_NUMBER;
	GameState gameState;
	gameState.Player1Data.Strategy = USER;
	gameState.Player2Data.Strategy = RANDOMLY;
	InitGame(&gameState, WITHOUT_REFILL, SMART, cardsPerColor);
	gameState.PrintUIData = TRUE;
	GiveCards(&gameState);
	int startingPlayerIndex = rand(time(NULL)) % 2;
	PlayerData *startingPlayer;
	while (gameState.Player1Data.HandCards.CardsCount != DECK_MAX_SIZE && gameState.Player2Data.HandCards.CardsCount != DECK_MAX_SIZE)
	{
		if (startingPlayerIndex == 0)
			startingPlayer = &gameState.Player1Data;
		else
			startingPlayer = &gameState.Player2Data;
		
		UIPrintPreBattleData(&gameState, startingPlayerIndex);
		SmartBattle(&gameState, startingPlayer);

		if (gameState.Winner == &gameState.Player1Data)
			break;
		else if (gameState.Winner == &gameState.Player2Data)
			break;

		startingPlayerIndex = (startingPlayerIndex + 1) % 2;
	}
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
	UIPrintGameEntryText();
	printf("> Podaj X aby wyjsc, Z, aby rozpoczac\n");
	if (!playerWantsToPlay())
		return;

	printf("> Podaj rozmiar talii (wpisz minimalny numer kart, ktore beda w talii (od %i do %i))?\n", MIN_CARD_NUMBER, MAX_CARD_NUMBER);
	startGame(getStartingCardNumber());
}