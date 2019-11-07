#include "Rank.h"
#include "Structures.h"

int GetPlayerRank(PlayerData *player)
{
	int output = 0;
	CardQueueItem *item = player -> HandCards.FirstCard;
	if (item == NULL)
		return output;

	if (item -> value.Number >= MIN_CARD_NUMBER_POINTING)
		output += item -> value.Number - MIN_CARD_NUMBER_POINTING + 1;

	for (int i = 1; i < player -> HandCards.AllCards; i++)
	{
		item = item -> next;
		if (item -> value.Number >= MIN_CARD_NUMBER_POINTING)
			output += item -> value.Number - MIN_CARD_NUMBER_POINTING + 1;
	}

	return output;
}