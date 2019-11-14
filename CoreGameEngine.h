#pragma once
#include "Structures.h"
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
typedef enum Strategy { DEFENSIVE, OFFENSIVE, RANDOM } Strategy;

typedef struct GameState
{
	int CardsPerColor;
	PlayerData Player1Data;
	PlayerData Player2Data;
	int RandomSeed;
	int TurnsCount;
	PlayerData *Winner;
	Strategy Strategy;
	WarOption WarOption;
} GameState;

void AddFirstCardToStack(PlayerData *player);
void HandleComparingCards(GameState *gameState);
void InitGame(GameState *gameState, WarOption warOption, int randomSeed);