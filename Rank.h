#pragma once

#include "StandardGameEngine.h"
//#define MIN_CARD_NUMBER_POINTING (8)

int GetCardRank(int cardNumber, int minCardNumberPointing);
int GetPlayerRank(PlayerData *player, int minCardNumberPointing);
int GetMaxRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount, int minCardNumberPointing);
int GetMinRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount, int minCardNumberPointing);
int GetMaxRankForDeckSize(int cardsPerColor, int minCardNumberPointing);
int GetMinRankForDeckSize(int cardsPerColor, int minCardNumberPointing);
