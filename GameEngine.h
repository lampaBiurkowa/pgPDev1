#pragma once

#include "Structures.h"

#define CARDS_TAKING_PART_IN_WAR (2)
#define COLORS_COUNT (4)
#define YOUNGEST_CARD_NUMBER (2)

typedef struct PlayerData
{
	CardsQueue HandCards;
	CardsQueue StackCards;
	int UsedEnemyCardsInWar;
} PlayerData;


typedef enum WarOption { WITH_REFILL, WITHOUT_REFILL } WarOption;

typedef struct GameState
{
	int CardsPerColor;
	PlayerData Player1Data;
	PlayerData Player2Data;
	int RandomSeed;
	int TurnsCount;
	PlayerData *Winner;
	WarOption WarOption;
} GameState;

void Battle(GameState *gameState);
void GiveCards(GameState *gameState);
void InitGame(GameState *gameState);
void War(GameState *gameState);