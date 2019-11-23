#pragma once

#include "StandardGameEngine.h"

void WriteInputData(const char *path, int cardsPerColor, int seed);
int GetCardNumbersFromFile(const char *path, int *arrayToFill);