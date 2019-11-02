#pragma once

#include "Structures.h"

#define COLORS_COUNT (4)
#define DECK_MAX_SIZE (52) // 4 talie * 13 kart
#define YOUNGEST_CARD_NUMBER (2)

typedef struct PlayerData
{
	CardsQueueItem AllCards[DECK_MAX_SIZE];
	CardsQueueItem *FirstHandCard;
	CardsQueueItem *LastHandCard;
	CardsQueueItem *FirstStackCard;
	CardsQueueItem *LastStackCard;
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
void GiveCards(int cardsPerColor, GameState* gameState);
void War(PlayerData* player1, PlayerData* player2);