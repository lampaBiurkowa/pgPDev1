#include "UserInterfaceDataPrinter.h"

void UIPrintChoiceData(CardQueueItem *usersCard, int startingPlayerIndex)
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

void UIPrintPreBattleData(GameState *gameState, int startingPlayerIndex)
{
	system("cls");

	printf("Moje karty (od poczatku reki):\n");
	PrintCardsQueue(&gameState -> Player1Data.HandCards);
	printf("Kolejka: %i, ilosc moich kart w rece: %i, ilosc kart przeciwnika w rece: %i.\n\n", gameState -> TurnsCount, gameState -> Player1Data.HandCards.CardsCount, gameState -> Player2Data.HandCards.CardsCount);
	UIPrintChoiceData(gameState -> Player1Data.HandCards.FirstCard, startingPlayerIndex);
	printf("> Kliknij dowolny klawisz, aby kontynuowac...\n\n");
	_getch();
}

void UIPrintGameEntryText()
{
	system("cls");
	printf("     === W o j n a ===\n");
	printf("       gra karciana\n\n\n");
}

void printWarInfo()
{
	printf("\n * * * * * W  O  J  N  A * * * * *\n");
}

void printTurnData(Card *userCard, Card *opponentCard)
{
	printf("Twoja karta: |%i %s| vs |%i %s| karta przeciwnika\n", userCard -> Number, GetCardSuitName(userCard -> Color), opponentCard -> Number, GetCardSuitName(opponentCard -> Color));
}

void printPostBattleData(Card *userCard, Card *opponentCard)
{
	const char* VICTORY_TEXTS[] = { "JEA!", "Zbierasz karty!", "Tak trzymac!", "Widac ze profesjonalista!" };
	const char* LOSE_TEXTS[] = { ":'(", "Nic sie nie stalo!", "Niestety tracisz karty...", "Nie poddawaj sie!" };
	int textIndex = rand() % 4;
	if (userCard -> Number > opponentCard -> Number)
		printf("\n*** WYGRYWASZ POJEDYNEK *** %s\n\n", VICTORY_TEXTS[textIndex]);
	else if (userCard -> Number < opponentCard -> Number)
		printf("\n*** PRZEGRYWASZ POJEDYNEK *** %s\n\n", LOSE_TEXTS[textIndex]);
}

void UIPrintMiddleWarTurnInfo(Card *userCard)
{
	printf("\nZagrywasz zakryta karte: |%i %s|, przeciwnik rowniez zagrywa zakryta karte\n\n", userCard -> Number, GetCardSuitName(userCard -> Color));
}

void UIPrintStandardTurnInfo(Card *userCard, Card *opponentCard)
{
	printTurnData(userCard, opponentCard);
	printPostBattleData(userCard, opponentCard);
}

void UIPrintWarCausingTurnInfo(Card *userCard, Card *opponentCard)
{
	printTurnData(userCard, opponentCard);
	printWarInfo();
}