#include "UserInterface.h"
#include "CardsDeliverer.h"
#include "SmartGameEngine.h"
#include <time.h>

#define CARDS_TO_SHOW_PER_ROW (8)

const char *getCardSuitName(CardColor color)
{
	switch (color)
	{
	case KARO:
		return "KARO";
	case KIER:
		return "KIER";
	case PIK:
		return "PIK";
	case TREFL:
		return "KIER";
	default:
		return "???";
	}
}

void showPreBattleData(GameState *gameState)
{
	system("cls");

	printf("Moje karty (od poczatku reki):\n");
	CardQueueItem *item = gameState -> Player1Data.HandCards.FirstCard;
	for (int i = 0; i < gameState -> Player1Data.HandCards.CardsCount; i++)
	{
		if (i % CARDS_TO_SHOW_PER_ROW == 0 && i != 0)
			printf("\n");

		printf("|%i %s| ", item -> value.Number, getCardSuitName(item -> value.Color));
		item = item -> previous;
	}

	printf("Szczyt mojego stosu (%i kart na stosie):\n", gameState -> Player1Data.StackCards.CardsCount);
	item = gameState -> Player1Data.StackCards.FirstCard;
	printf("|%i %s|");

	printf("Szczyt stosu przeciwnika (%i kart na stosie):\n", gameState -> Player2Data.StackCards.CardsCount);
	item = gameState -> Player2Data.StackCards.FirstCard;
	printf("|%i %s|");

	printf("\nKolejka: %i, ilosc moich kart w rece: %i, ilosc kart przeciwnika w rece: %i", gameState -> TurnsCount, gameState -> Player1Data.HandCards.CardsCount, gameState -> Player2Data.HandCards.CardsCount);
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