#pragma once

#include "Structures.h"

#define COLORS_COUNT (4)
#define DECK_MAX_SIZE (52)
#define YOUNGEST_CARD_NUMBER (2)

typedef struct PlayerData
{
	CardsQueue HandCards;
	CardsQueue StackCards;
	int UsedEnemyCardsInWar;
	int HandCardsCount;
	int StackCardsCount;
} PlayerData;

typedef struct GameState
{
	PlayerData Player1Data;
	PlayerData Player2Data;
	PlayerData *ActivePlayer;
} GameState;

void Battle(PlayerData* player1, PlayerData* player2);
void GiveCards(int cardsPerColor);
void War(PlayerData* player1, PlayerData* player2);