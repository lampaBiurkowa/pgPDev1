#pragma once

#include "StandardGameEngine.h"
#define MIN_CARD_NUMBER_POINTING (8)

int GetCardRank(int cardNumber);
int GetPlayerRank(PlayerData *player);
int GetMaxRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount);
int GetMinRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount);
int GetMaxRankForDeckSize(int cardsPerColor);
int GetMinRankForDeckSize(int cardsPerColor);
