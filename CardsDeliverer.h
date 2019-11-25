#pragma once
#include "StandardGameEngine.h"

void AssignCardNumbersFromArray(GameState *gameState, int *cardNumbers, int cardsCount);
void GiveCards(GameState *gameState);
void GetCardsForRank(GameState *gameState, int rank);
void ShuffleCards(CardsQueue *queue);