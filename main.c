#include "TestingService.h"

void generateTestFiles(int cardsPerColor)
{
	char path[16] = "syf/hownoXX.txt";
	for (int i = 0; i < 100; i++)
	{
		path[9] = ((int)'0' + i / 10);
		path[10] = ((int)'0' + i % 10);
		WriteInputData(path, cardsPerColor, i);
	}
}

void printMenu()
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
}

int main()
{
	int choice;
	printMenu();
	while (1)
	{
		while (scanf_s("%i", &choice))
		{
			switch (choice)
			{
			case 1:
				StandardGameProblem1();
				break;
			case 2:
				StandardGameProblem2();
				break;
			case 3:
				Demonstrate();
				break;
			case 4:
				SmartGameProblem1();
				break;
			case 5:
				SmartGameProblem2();
				break;
			case 6:
				ShowEntryScreen();
				break;
			case 7:
				EfficentStrategy();
				break;
			case 8:
				PlayFromFile();
				break;
			default:
				printf("Prosze wpisac poprawna cyfre");
			}
		}
		printMenu();
	}

	return 0;
}