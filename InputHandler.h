#pragma once

#include "StandardGameEngine.h"

void WriteInputData(const char *path, int cardsPerColor, int seed);
GameState ReadInputData(const char *path);