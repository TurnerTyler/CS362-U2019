#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int minion_helper(int choice1, int choice2, struct gameState *state, int handPos){
     int currentPlayer = whoseTurn(state);
     state->numActions++;

     //discard card from hand
     discardCard(handPos, currentPlayer, state, 0);

     if (choice1)		//+2 coins
     {
          add_coin(state, 2);
     }

     else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
     {
          //discard hand
          while(numHandCards(state) > 0)
          {
               discardCard(handPos, currentPlayer, state, 0);
          }

          //draw 4
          for (int i = 0; i < 4; i++)
          {
               drawCard(currentPlayer, state);
          }

          //other players discard hand and redraw if hand size > 4
          for (int j = 0; j < state->numPlayers; j++)
          {
               if (j != currentPlayer)
               {
                    if ( state->handCount[j] > 4 )
                    {
                         //discard hand
                         while( state->handCount[j] > 0 )
                         {
                              discardCard(handPos, j, state, 0);
                         }

                         //draw 4
                         for (j = 0; j < 4; j++)
                         {
                              drawCard(j, state);
                         }
                    }
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
  int choice2;
  int i = 0;
  int j = 0;
  int x = 0;
  int n = 0;
  int p = 0;
  int kin = 1;
  int prevsupply;
  int currentPlayer = 0;
  //set silence to 1 to see errors
  int silence = 1;

  SelectStream(1);
  PlantSeeds(1245);

  for(i=0; i<150000; i++){
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

    x = floor(Random() * numPlayers);
    if(x == 0){
      x = x + 2;
    }
    else if(x + 1 < numPlayers){
      x++;
    }
    state.handCount[x-1] = 0;

    x = floor(Random() * 10);
    if(x > 5){
      choice1 = 1;
    }
    else{
      choice1 = 0;
    }

    if(x > 5){
      choice2 = 0;
    }
    else{
      choice2 = 1;
    }

    //initialize game state
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);

    state.hand[currentPlayer][1] = minion;

    minion_helper(1, choice1, choice2, &state);

    if(choice1){
      if(state.coins != 2 && silence == 0){
        printf("Coins not added\n");
      }
      if(state.handCount[currentPlayer] != 4 && silence == 0){
        printf("didn't discard\n");
      }
    }
    else{
      for(j=0;j<numPlayers;j++){
        if(state.handCount[j] != 4 && silence == 0){
          printf("hand count wrong\n");
        }
      }
    }

}
}
