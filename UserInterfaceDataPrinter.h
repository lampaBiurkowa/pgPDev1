#pragma once
#include "SmartGameEngine.h"

void UIPrintChoiceData(CardQueueItem *usersCard, int startingPlayerIndex);
void UIPrintPreBattleData(GameState *gameState, int startingPlayerIndex);
void UIPrintGameEntryText();
void UIPrintMiddleWarTurnInfo(Card *userCard);
void UIPrintWarCausingTurnInfo(Card *userCard, Card *opponentCard);
void UIPrintStandardTurnInfo(Card *userCard, Card *opponentCard);