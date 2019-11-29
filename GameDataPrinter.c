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
	printf("\n");
}

void printGenericTurnData(GameState *gameState)
{
	printf("\n==========Ruch nr %i ===========\n", gameState -> TurnsCount);
	printf("Karty w rece Gracza 1 (od pierwszej karty):\n");
	PrintCardsQueue(&gameState -> Player1Data.HandCards);
	printf("\nKarty w rece Gracza 2 (od pierwszej karty):\n");
	PrintCardsQueue(&gameState -> Player2Data.HandCards);
}

void printStandardPlayersCardPlayed(GameState *gameState)
{
	Card player1CurrentCard = gameState -> Player1Data.StackCards.FirstCard -> value;
	printf("Gracz 1 zagrywa: %i %s, ", player1CurrentCard.Number, GetCardSuitName(player1CurrentCard.Color));
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
	printf("             *** W O J N A ***\n");
}


void PrintWarCausingTurnData(GameState *gameState)
{
	printf("siema PrintWarCausingTurnData\n");
	printGenericTurnData(gameState);
	printStandardPlayersCardPlayed(gameState);
	printWarStartedIndicator();
}

void PrintWarWithSmallRefillTurnData(GameState *gameState, PlayerData *helpingPlayer)
{
	printf("siema PrintWarWithSmallRefillTurnData\n");
	printGenericTurnData(gameState);

	int helpingPlayerNumber;
	if (helpingPlayer == &gameState -> Player1Data)
		helpingPlayerNumber = 1;
	else
		helpingPlayerNumber = 2;

	Card firstCard = helpingPlayer -> HandCards.FirstCard -> value;
	Card secondCard = helpingPlayer -> HandCards.FirstCard -> previous -> value;
	printf("Gracz %i zagrywa dla Gracza %i: %i %s, ", helpingPlayerNumber, (helpingPlayerNumber + 1) % 2, firstCard.Number, GetCardSuitName(firstCard.Color));
	printf("Gracz %i zagrywa dla Gracza %i: %i %s, ", helpingPlayerNumber, helpingPlayerNumber, secondCard.Number, GetCardSuitName(secondCard.Color));
}

void PrintFirstPartWarWithBigRefillTurnData(GameState *gameState, PlayerData *helpingPlayer)
{
	printf("siema PrintFirstPartWarWithBigRefillTurnData\n");
	printGenericTurnData(gameState);

	int helpingPlayerNumber;
	if (helpingPlayer == &gameState -> Player1Data)
		helpingPlayerNumber = 1;
	else
		helpingPlayerNumber = 2;

	Card firstCard = helpingPlayer -> HandCards.FirstCard -> value;
	Card secondCard = helpingPlayer -> HandCards.FirstCard -> previous -> value;
	printf("Gracz %i zagrywa dla Gracza %i: %i %s, ", helpingPlayerNumber, (helpingPlayerNumber + 1) % 2, firstCard.Number, GetCardSuitName(firstCard.Color));
	printf("Gracz %i zagrywa dla Gracza %i: %i %s, ", helpingPlayerNumber, (helpingPlayerNumber + 1) % 2, secondCard.Number, GetCardSuitName(secondCard.Color));
}

void PrintSecondPartWarWithBigRefillTurnData(GameState *gameState, PlayerData *helpingPlayer)
{
	printf("siema PrintSecondPartWarWithBigRefillTurnData\n");
	printGenericTurnData(gameState);

	int helpingPlayerNumber;
	if (helpingPlayer == &gameState -> Player1Data)
		helpingPlayerNumber = 1;
	else
		helpingPlayerNumber = 2;

	Card firstCard = helpingPlayer -> HandCards.FirstCard -> value;
	Card secondCard = helpingPlayer -> HandCards.FirstCard -> previous -> value;
	printf("Gracz %i zagrywa dla gracza %i: %i %s, ", helpingPlayerNumber, helpingPlayerNumber, firstCard.Number, GetCardSuitName(firstCard.Color));
	printf("Gracz %i zagrywa dla gracza %i: %i %s, ", helpingPlayerNumber, helpingPlayerNumber, secondCard.Number, GetCardSuitName(secondCard.Color));
}