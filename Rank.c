#include "Rank.h"
#include "Structures.h"

int GetCardRank(int cardNumber)
{
	if (cardNumber < MIN_CARD_NUMBER_POINTING)
		return 0;

	return cardNumber - MIN_CARD_NUMBER_POINTING + 1;
}

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