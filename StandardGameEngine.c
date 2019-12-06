#include "StandardGameEngine.h"

void Battle(GameState *gameState)
{
	gameState -> TurnsCount++;
	AddFirstCardToStack(&gameState -> Player1Data);
	AddFirstCardToStack(&gameState -> Player2Data);

	HandleComparingCards(gameState);
}