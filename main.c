#include "TestingService.h"

void generateTestFiles()
{
	char path[16] = "syf/hownoXX.txt";
	for (int i = 0; i < 100; i++)
	{
		path[9] = ((int)'0' + i / 10);
		path[10] = ((int)'0' + i % 10);
		WriteInputData(path, 13, i);
	}
}

int main()
{
	int choice;
	while (1)
	{
		while (scanf_s("%i", &choice))
		{
			printf("Wybierz:\n");
			printf("1 - pokazac wyniki problemu 1 gry w zwykla wojne\n");
			printf("2 - pokazac wyniki problemu 2 gry w zwykla wojne\n");
			printf("3 - zademonstrowac zwykla wojne\n");
			printf("4 - pokazac wyniki problemu 1 gry w madra wojne\n");
			printf("5 - pokazac wyniki problemu 2 gry w madra wojne\n");
			printf("6 - zagrac z komputerem w madra wojne\n");
			printf("7 - pokazac wyniki strategii gry w madra wojne na dodatkowe punkty\n");
			printf("8 - pokazac wyniki gier z plikow\n");

			switch (choice)
			{
			case 1:
				standardGameProblem1();
				break;
			case 2:
				standardGameProblem2();
				break;
			case 3:
				Demonstrate();
				break;
			case 4:
				smartGameProblem1();
				break;
			case 5:
				smartGameProblem2();
				break;
			case 6:
				ShowEntryScreen();
				break;
			case 7:
				efficentStrategy();
				break;
			case 8:
				playFromFile();
				break;
			default:
				printf("Prosze wpisac poprawna cyfre");
			}
		}
	}

	return 0;
}