#pragma once
#include "Structures.h"

#define CARDS_TAKING_PART_IN_WAR (2)
#define COLORS_COUNT (4)
#define YOUNGEST_CARD_NUMBER (2)

typedef enum GameRules { STANDARD, SMART } GameRules;
typedef enum Strategy { DEFENSIVE, OFFENSIVE, RANDOMLY, USER } Strategy;
typedef enum WarOption { WITH_REFILL, WITHOUT_REFILL } WarOption;

typedef struct PlayerData
{
	CardsQueue HandCards;
	CardsQueue StackCards;
	Strategy Strategy;
	int UsedEnemyCardsInWar;

} PlayerData;

typedef struct GameState
{
	int CardsPerColor;
	GameRules GameRules;
	PlayerData Player1Data;
	PlayerData Player2Data;
	int RandomSeed;
	int TurnsCount;
	WarOption WarOption;
	PlayerData *Winner;
} GameState;

void AddFirstCardToStack(PlayerData *player);
void HandleComparingCards(GameState *gameState);
void InitGame(GameState *gameState, WarOption warOption, GameRules gameRules, int cardsPerColor);
void ResetGame(GameState *gameState);