#include "Structures.h"

Card PopFrontCard(CardsQueue* queue)
{
	Card value = queue -> FirstCard -> value;
	queue -> FirstCard = queue -> FirstCard -> previous;
	queue -> CardsCount--;
	return value;
}