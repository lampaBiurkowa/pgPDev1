#pragma once
#include "StandardGameEngine.h"

void AssignCardNumbersFromArray(GameState *gameState, int *cardNumbers, int cardsCount);
void GiveCards(GameState *gameState);
void GetCardsForRank(GameState *gameState, int rank, int minCardPointingNumber);
void ShuffleCards(CardsQueue *queue);