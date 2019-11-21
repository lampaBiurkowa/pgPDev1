#pragma once
#include "StandardGameEngine.h"
#define MIN_CARD_NUMBER (2)
#define MAX_CARD_NUMBER (14)

void GiveCards(GameState *gameState);
void GetCardsForRank(int rank, GameState *gameState);
void ShuffleCards(CardsQueue *queue);