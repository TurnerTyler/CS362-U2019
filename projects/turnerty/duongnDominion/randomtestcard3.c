#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int tributeRevealedCards[2] = {-1, -1};

int tribute_helper(struct gameState *state){
     int currentPlayer = whoseTurn(state);
     int nextPlayer = currentPlayer + 1;
     int tributeRevealedCards[2] = {-1, -1};
     if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1){
          if (state->deckCount[nextPlayer] > 0){
               tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
               state->deckCount[nextPlayer]--;
          }
          else if (state->discardCount[nextPlayer] > 0){
               tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
               state->discardCount[nextPlayer]--;
          }
          else{
               //No Card to Reveal
               if (DEBUG){
                    printf("No cards to reveal\n");
               }
          }
     }

     else{
          if (state->deckCount[nextPlayer] == 0){
               for (int i = 0; i < state->discardCount[nextPlayer]; i++){
                    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                    state->deckCount[nextPlayer]++;
                    state->discard[nextPlayer][i] = -1;
                    state->discardCount[nextPlayer]--;
               }

               shuffle(nextPlayer,state);//Shuffle the deck
          }
          tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
          state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
          state->deckCount[nextPlayer]--;
          tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
          state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
          state->deckCount[nextPlayer]--;
     }

     if (tributeRevealedCards[0] == tributeRevealedCards[1]){//If we have a duplicate card, just drop one
          state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
          state->playedCardCount++;
          tributeRevealedCards[1] = -1;
     }

     for (int i = 0; i <= 2; i ++){
          if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold){//Treasure cards
               state->coins += 2;
          }

          else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){//Victory Card Found
               drawCard(currentPlayer, state);
               drawCard(currentPlayer, state);
          }
          else{//Action Card
               state->numActions = state->numActions + 2;
          }
     }

     return 0;
}

int main(){
  int numPlayers;
  int kingdomCards[10];
  int randomSeed;
  struct gameState state;
  int choice;
  int i = 0;
  int j = 0;
  int x = 0;
  int n = 0;
  int p = 0;
  int kin = 1;
  int prevDeckCount;
  int prevNumActions;
  int prevCards;
  int prevCoins;
  int currentPlayer;
  //set silence to 1 to see errors
  int silence = 1;

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

    prevDeckCount = state.deckCount[currentPlayer + 1];
    prevNumActions = state.numActions;
    prevCards = state.handCount[currentPlayer];
    prevCoins = state.coins;

    tribute_helper(&state);

    if(state.deckCount[currentPlayer + 1] != prevDeckCount - 2 && silence == 0){
      printf("Failed to discard 2 cards from next players deck\n");
    }
    for(x=0;x<2;x++){
      if(x == 0){
        if(tributeRevealedCards[x] == tributeRevealedCards[x+1]){
          x = 1;
        }
      }
      if (tributeRevealedCards[x] == copper || tributeRevealedCards[x] == silver || tributeRevealedCards[x] == gold){//Treasure cards
        if(prevCoins != state.coins - 2 && silence == 0){
          printf("failed to add coins\n");
        }
        prevCoins = state.coins;
      }
      else if(tributeRevealedCards[x] == estate || tributeRevealedCards[x] == duchy || tributeRevealedCards[x] == province || tributeRevealedCards[x] == gardens || tributeRevealedCards[x] == great_hall){//Victory Card Found)
        if(prevCards != state.handCount[currentPlayer] - 2 && silence == 0){
          printf("failed to add to cards to player\n");
        }
        prevCards = state.handCount[currentPlayer];
      }
      else{
        if(prevNumActions != state.numActions - 2 && silence == 0){
          printf("failed to add two action points\n");
        }
        prevNumActions = state.numActions;
      }
    }

  }
}
