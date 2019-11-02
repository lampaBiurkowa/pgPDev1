#pragma once

#include "Structures.h"

#define COLORS_COUNT (4)
#define YOUNGEST_CARD_NUMBER (2)

typedef struct PlayerData
{
	CardsQueue HandCards;
	CardsQueue StackCards;
	int UsedEnemyCardsInWar;
} PlayerData;

typedef struct GameState
{
	PlayerData Player1Data;
	PlayerData Player2Data;
	PlayerData *ActivePlayer;
} GameState;

void Battle(PlayerData* player1, PlayerData* player2);
void GiveCards(int cardsPerColor, GameState* gameState);
void War(PlayerData* player1, PlayerData* player2);