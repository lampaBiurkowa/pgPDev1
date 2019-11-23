#pragma once
#include "StandardGameEngine.h"

void GiveCards(GameState *gameState);
void GetCardsForRank(int rank, GameState *gameState);
void ShuffleCards(CardsQueue *queue);