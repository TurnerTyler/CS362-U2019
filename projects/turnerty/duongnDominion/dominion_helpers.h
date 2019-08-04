#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

/* My own helper functions*/
int mine_helper(int choice1, int choice2, struct gameState *state, int handPos);
int baron_helper(int choice1, struct gameState *state);
void add_coin(struct gameState *state, int num_coins);
int minion_helper(int choice1, int choice2, struct gameState *state, int handPos);
int ambassador_helper(int choice1, int choice2, struct gameState *state, int handPos);
int tribute_helper( struct gameState *state);
#endif
