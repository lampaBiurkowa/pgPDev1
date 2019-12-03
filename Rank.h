#pragma once

#include "StandardGameEngine.h"

int GetCardRank(int cardNumber, int minCardNumberPointing);
int GetArrayRank(Card array[], int size, int minCardNumberPointing);
int GetQueueRank(CardsQueue *queue, int minCardNumberPointing);
int GetMaxRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount, int minCardNumberPointing);
int GetMinRankReachable(int cardsAmount, Card cardsDisabled[], int cardsDisabledCount, int minCardNumberPointing);
int GetMaxRankForDeckSize(int cardsPerColor, int minCardNumberPointing);
int GetMinRankForDeckSize(int cardsPerColor, int minCardNumberPointing);
Card GetRandomCardForRank(int rank, int minCardNumberPointing);
