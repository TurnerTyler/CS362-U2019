#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
  int numPlayers;
  int kingdomCards[10];
  int randomSeed;
  struct gameState state;
  int choice;
  int i = 0;
  int j = 0;
  int prevsupply;
  int prevcoins;

  while(1){
    //random set number of players between 2 and MAX_PLAYERS
    numPlayers = (int) Random();
    numPlayer = numPlayers % MAX_PLAYERS;
    if(numPlayers < 2){
      numPlayers = numPlayers + 2;
    }
    //set random seed
    randomSeed = (int) Random();

    //set random kingdomCards

    //initialize game state
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);

    //random choice
    choice = (int) Random();
    choice = choice % 1;

    //call baron function and test result
    prevsupply = supplyCount(estate, &state);
    prevcoins = state.coins;
    if(choice == 0){
      baron(choice, &state);
      assert(supplyCount(estate, &state) == prevsupply + 1);
      assert(state.coins == prevcoins);
    }
    else{
      baron(choice, &state);
      assert(supplyCount(estate, &state) == prevsupply);
      assert(state.coins == prevcoins + 4);
    }


  }
}

int baron(int choice, struct gameSate *state)
{
  int currentPlayer = whoseTurn(state);
  if (choice > 0){//Boolean true or going to discard an estate
    int p = 0;//Iterator for hand!
    int card_not_discarded = 0;//Flag for discard set!
    while(card_not_discarded){
      if (state->hand[currentPlayer][p] == estate){//Found an estate card!
        state->coins += 4;//Add 4 coins to the amount of coins
        state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
        state->discardCount[currentPlayer]++;
        for (p < state->handCount[currentPlayer]; p++){
          state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
        }
        state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
        state->handCount[currentPlayer]--;
        card_not_discarded = 0;//Exit the loop
      }
      else if (p > state->handCount[currentPlayer]){
        if(DEBUG) {
          printf("No estate cards in your hand, invalid choice\n");
          printf("Must gain an estate if there are any\n");
        }
        if (supplyCount(estate, state) > 0){
          gainCard(estate, state, 0, currentPlayer);
          state->supplyCount[estate]--;//Decrement estates
          if (supplyCount(estate, state) == 0){
            isGameOver(state);
          }
        }
        card_not_discarded = 0;//Exit the loop
      }

      else{
        p++;//Next card
      }
    }
  }

  else{
    if (supplyCount(estate, state) > 0){
      gainCard(estate, state, 0, currentPlayer);//Gain an estate
      state->supplyCount[estate]--;//Decrement Estates
      if (supplyCount(estate, state) == 0){
        isGameOver(state);
      }
    }
  }


  return 0;
}
