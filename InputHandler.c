#include <stdio.h>
#include "CardsDeliverer.h"
#include "InputHandler.h"

void WriteInputData(const char *path, int cardsPerColor, int seed)
{
	srand(time(NULL) + seed);
	FILE *file;
	fopen_s(&file, path, "w");
	GameState gameState;
	InitGame(&gameState, WITHOUT_REFILL, STANDARD, cardsPerColor);
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

char *getReadInputPattern(int cardsAmount)
{
	const int PATTERN_CHARS_PER_NUMBER_COUNT = 4;
	char *output = (char *)malloc(sizeof(char) * cardsAmount * PATTERN_CHARS_PER_NUMBER_COUNT);
	for (int i = 0; i < cardsAmount * PATTERN_CHARS_PER_NUMBER_COUNT; i += PATTERN_CHARS_PER_NUMBER_COUNT)
	{
		output[i] = '%';
		output[i + 1] = '0';
		output[i + 2] = '2';
		output[i + 3] = 'i';
	}

	return output;
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

GameState ReadInputData(const char *path)
{
	FILE *file;
	fopen_s(&file, path, "r");

	int nums[DECK_MAX_SIZE];
	int size = getInputDeckSize(file);
	for (int i = 0; i < size; i++)
	{
		fseek(file, i * 2, SEEK_SET);
		fscanf_s(file, "%02d", &nums[i]);
	}

	fclose(file);
}