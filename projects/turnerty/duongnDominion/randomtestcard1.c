#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int baron_helper(int choice1, struct gameState *state){
     int currentPlayer= whoseTurn(state);
     state->numBuys++;//Increase buys by 1!
     if (choice1 > 0){//Boolean true or going to discard an estate
          int p = 0;//Iterator for hand!
          int card_not_discarded = 1;//Flag for discard set!
          while(card_not_discarded){
               if (state->hand[currentPlayer][p] == estate){//Found an estate card!
                    state->coins += 4;//Add 4 coins to the amount of coins
                    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
                    state->discardCount[currentPlayer]++;
                    for (;p < state->handCount[currentPlayer]; p++){
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

int main(){
  int numPlayers;
  int kingdomCards[10];
  int randomSeed;
  struct gameState state;
  int choice1;
  int i = 0;
  int j = 0;
  int x = 0;
  int n = 0;
  int p = 0;
  int kin = 1;
  int prevsupply;
  int prevcoins;
  int currentPlayer;
  //set silence to 1 to see errors
  int silence = 0;

  SelectStream(1);
  PlantSeeds(1245);

  for(i=0; i<1000000; i++){
    state.coins = 0;
    //random set number of players between 2 and MAX_PLAYERS
    numPlayers = floor(Random() * MAX_PLAYERS);
    if(numPlayers < 2){
      numPlayers = numPlayers + 2;
    }

    //select a random player to be the current player
    currentPlayer = floor(Random() * numPlayers);

    //set random seed
    randomSeed = floor(Random() * 1234);

    //set random kingdomCards
    for(j=0; j<10; j++){
      kin = 1;
      while(kin == 1 && j > 0){
        x = floor(Random() * 27);
        kin = 0;
        for(n=0;n<j;n++){
          if(kingdomCards[n] == x){
            kin = 1;
          }
        }
        kingdomCards[j] = x;
      }
    }

    //initialize game state
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);

    x = floor(Random() * 10);
    state.supplyCount[estate] = x;

    //random choice
    x = floor(Random() * 10);
    if(x > 5){
      choice1 = 1;
    }
    else{
      choice1 = 0;
    }

    //call baron function and test result
    prevsupply = supplyCount(estate, &state);
    prevcoins = state.coins;
    p = 0;
    for(p=0; p<state.handCount[currentPlayer];p++){
      if(state.hand[currentPlayer][p] == estate){
        break;
      }
    }
    if(choice1 == 0){
      baron_helper(choice1, &state);

      if(supplyCount(estate, &state) != prevsupply + 1 && silence == 1)
      {
        printf("Supply Count did not update.\n");
      }
      if(state.coins != prevcoins && silence == 1){
        printf("Coins added when shouldn't.\n");
      }

    }
    else{
      if(state.hand[currentPlayer][p] == estate){
        prevsupply = supplyCount(estate, &state);
        baron_helper(choice1, &state);

        if(supplyCount(estate, &state) != prevsupply && silence == 1){
          printf("Supply estate cards altered when shouldn't.\n");
        }
        if(state.coins != prevcoins + 4){
          printf("Did not get coins.\n");
        }

      }
      else{
        prevsupply = supplyCount(estate, &state);
        baron_helper(choice1, &state);
        if(prevsupply < 1){

          if(prevsupply != supplyCount(estate, &state) && silence == 1){
            printf("Supply estate cards altered when shouldn't.\n");
          }

        }
        if(prevsupply > 0){

          if(prevsupply != supplyCount(estate, &state) + 1 && silence == 1){
            printf("Supply not altered.\n");
          }

          for(p=0; p<state.handCount[currentPlayer];p++){
            if(state.hand[currentPlayer][p] == estate){
              break;
            }
          }

          if(state.hand[currentPlayer][p] != estate && silence == 1){
            printf("estate not added to hand\n");
          }

      }
    }
  }
}
}
