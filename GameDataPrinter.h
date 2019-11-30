#pragma once

#include "CoreGameEngine.h"
#include "Structures.h"

#define CARDS_TO_SHOW_PER_ROW (8)

void PrintCardsQueue(CardsQueue *queue);
void PrintWarWithSmallRefillTurnData(GameState *gameState, PlayerData *helpingPlayer);
void PrintFirstPartWarWithBigRefillTurnData(GameState *gameState, PlayerData *helpingPlayer);
void PrintSecondPartWarWithBigRefillTurnData(GameState *gameState, PlayerData *helpingPlayer);
void PrintWarCausingTurnData(GameState *gameState);
void PrintStandardTurnData(GameState *gameState);
void PrintVictoryInfo(GameState *gameState);
void PrintWarWonInfo(GameState *gameState, PlayerData *winner);