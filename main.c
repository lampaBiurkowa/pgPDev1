#include "TestingService.h"

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
}

int main()
{
	int choice;
	printMenu();
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
			PlayWithComputer();
			break;
		case 7:
			EfficentStrategy();
			break;
		default:
			printf("Prosze wpisac poprawna cyfre");
		}
		printMenu();
	}

	return 0;
}