#pragma once
#include <stdio.h>
#include "StandardGameEngine.h"
#include "SmartGameEngine.h"
#include "GameTester.h"
#include "InputHandler.h"
#include "Structures.h"
#include "Rank.h"
#include "CardsDeliverer.h"
#include "UserInterface.h"

#define CARDS_TO_SHOW_PER_ROW (8)
#define SIM_STRATEGY_DEFAULT (RANDOMLY)
#define SIM_RANK_DEFAULT (0)
#define SIM_MIN_CARD_NUM_POINTING (2)
#define SIM_SEED_DEFAULT (0)

void StandardGameProblem1();
void StandardGameProblem2();
void SmartGameProblem1();
void SmartGameProblem2();
void EfficentStrategy();
void PlayFromFile();
void PrintCardsQueue(CardsQueue *queue);