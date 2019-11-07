#include <stdio.h>
#include "InputReader.h"

GameState ReadGameState(const char *path)
{
	FILE *file;
	//file = fopen(path, "w");
	printf("%i asasd", fopen_s(&file, path, "r"));
	int i = 0;
	char line[52];
	while (fgets(line, sizeof(line), file) && i < 20)
	{
		printf(line);
		printf(" jea \n");
		i++;
	}
	fclose(file);
}