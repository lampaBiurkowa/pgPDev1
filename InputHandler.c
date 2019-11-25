#include <stdio.h>
#include "CardsDeliverer.h"
#include "InputHandler.h"

void WriteInputData(const char *path, int cardsPerColor, int seed)
{
	FILE *file;
	fopen_s(&file, path, "w");
	GameState gameState;
	InitGame(&gameState, WITHOUT_REFILL, STANDARD, cardsPerColor);
	gameState.RandomSeed = seed;
	GiveCards(&gameState);
	CardQueueItem *item = gameState.Player1Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player1Data.HandCards.CardsCount; i++)
	{
		fprintf(file, "%02i", item -> value.Number);
		item = item -> previous;
	}
	item = gameState.Player2Data.HandCards.FirstCard;
	for (int i = 0; i < gameState.Player2Data.HandCards.CardsCount; i++)
	{
		fprintf(file, "%02i", item -> value.Number);
		item = item -> previous;
	}
	fclose(file);
}

int getInputDeckSize(FILE *file)
{
	int size = 0;
	char line[DECK_MAX_SIZE * 2]; // TODO define? 2 bytes per number
	while (fgets(line, sizeof(line), file))
	{
		for (; size < sizeof(line); size++)
			if (line[size] == '\0')
				break;
	}

	return size / 2 + 1; //TODO jw
}

int GetCardNumbersFromFile(const char *path, int *arrayToFill)
{
	FILE *file;
	fopen_s(&file, path, "r");

	int deckSize = getInputDeckSize(file);
	for (int i = 0; i < deckSize; i++)
	{
		fseek(file, i * 2, SEEK_SET);
		fscanf_s(file, "%02d", &arrayToFill[i]);
	}

	fclose(file);
	return deckSize;
}