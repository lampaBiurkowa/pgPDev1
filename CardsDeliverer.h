#pragma once
#include "StandardGameEngine.h"

void AssignCardNumbersFromArray(GameState *gameState, int *cardNumbers, int cardsCount);
void GiveCards(GameState *gameState);
void GetCardsForRank(int rank, GameState *gameState);
void ShuffleCards(CardsQueue *queue);