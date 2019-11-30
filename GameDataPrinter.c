#include "GameDataPrinter.h"

void PrintCardsQueue(CardsQueue *queue)
{
	CardQueueItem *item = queue -> FirstCard;
	for (int i = 0; i < queue -> CardsCount; i++)
	{
		if (i % CARDS_TO_SHOW_PER_ROW == 0 && i != 0)
			printf("\n");

		printf("|%i %s| ", item -> value.Number, GetCardSuitName(item -> value.Color));
		item = item -> previous;
	}

	if (queue -> CardsCount == 0)
		printf("Brak kart :(");

	printf("\n");
}

void printGenericTurnData(GameState *gameState)
{
	printf("\n     ========== Ruch nr %i ===========\n\n", gameState -> TurnsCount);
	printf("Karty w rece Gracza 1 (od pierwszej karty):\n");
	PrintCardsQueue(&gameState -> Player1Data.HandCards);
	printf("\nKarty w rece Gracza 2 (od pierwszej karty):\n");
	PrintCardsQueue(&gameState -> Player2Data.HandCards);
}

void printStandardPlayersCardPlayed(GameState *gameState)
{
	Card player1CurrentCard = gameState -> Player1Data.StackCards.FirstCard -> value;
	printf("\nGracz 1 zagrywa: %i %s, ", player1CurrentCard.Number, GetCardSuitName(player1CurrentCard.Color));
	Card player2CurrentCard = gameState -> Player2Data.StackCards.FirstCard -> value;
	printf("Gracz 2 zagrywa: %i %s\n", player2CurrentCard.Number, GetCardSuitName(player2CurrentCard.Color));
}

void PrintStandardTurnData(GameState *gameState)
{
	printGenericTurnData(gameState);
	printStandardPlayersCardPlayed(gameState);
}

void printWarStartedIndicator()
{
	printf("\n             *** W O J N A ***\n");
}

void PrintWarCausingTurnData(GameState *gameState)
{
	printGenericTurnData(gameState);
	printStandardPlayersCardPlayed(gameState);
	printWarStartedIndicator();
}

int getPlayerNumber(GameState *gameState, PlayerData *helpingPlayer)
{
	if (helpingPlayer == &gameState -> Player1Data)
		return 1;

	return 2;
}

int getOppositePlayerNumber(int basePlayerNumber)
{
	return 2 - (basePlayerNumber + 1) % 2; //2 - parzystosc numeru przeciwnika
}

void printRefillTurnData(GameState *gameState, PlayerData *helpingPlayer, int firstGiftedNumber, int secondGiftedNumber)
{
	int helpingPlayerNumber = getPlayerNumber(gameState, helpingPlayer);
	Card firstCard = helpingPlayer -> HandCards.FirstCard -> value;
	Card secondCard = helpingPlayer -> HandCards.FirstCard -> previous -> value;
	printf("Gracz %i zagrywa dla Gracza %i: %i %s, ", helpingPlayerNumber, firstGiftedNumber, firstCard.Number, GetCardSuitName(firstCard.Color));
	printf("Gracz %i zagrywa dla Gracza %i: %i %s\n", helpingPlayerNumber, secondGiftedNumber, secondCard.Number, GetCardSuitName(secondCard.Color));

}

void PrintWarWithSmallRefillTurnData(GameState *gameState, PlayerData *helpingPlayer)
{
	printGenericTurnData(gameState);

	int helpingPlayerNumber = getPlayerNumber(gameState, helpingPlayer);
	printRefillTurnData(gameState, helpingPlayer, getOppositePlayerNumber(helpingPlayerNumber), helpingPlayerNumber);
}

void PrintFirstPartWarWithBigRefillTurnData(GameState *gameState, PlayerData *helpingPlayer)
{
	printGenericTurnData(gameState);

	int helpingPlayerNumber = getPlayerNumber(gameState, helpingPlayer);
	printRefillTurnData(gameState, helpingPlayer, getOppositePlayerNumber(helpingPlayerNumber), getOppositePlayerNumber(helpingPlayerNumber));
}

void PrintSecondPartWarWithBigRefillTurnData(GameState *gameState, PlayerData *helpingPlayer)
{
	printGenericTurnData(gameState);

	int helpingPlayerNumber = getPlayerNumber(gameState, helpingPlayer);
	printRefillTurnData(gameState, helpingPlayer, helpingPlayerNumber, helpingPlayerNumber);
}

void PrintVictoryInfo(GameState *gameState)
{
	if (gameState -> Winner == &gameState -> Player1Data)
		printf("\nWYGRAL GRACZ 1!!!!!\n");
	else
		printf("\nWYGRAL GRACZ 2!!!!!\n");
}

void PrintWarWonInfo(GameState *gameState, PlayerData *winner)
{
	printf("\nGracz %i wygrywa wojne!\n", getPlayerNumber(gameState, winner));
}