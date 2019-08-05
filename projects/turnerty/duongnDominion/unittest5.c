#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main(){
  int i;
  int numPlayers;
  int kingdomCards[10];
  int randomSeed;
  struct gameState s;
  int currentPlayer;
  int choice1;
  int choice2;
  int handPos;

  //test 1
  numPlayers = 3;
  kingdomCards[0] = 4;
  kingdomCards[1] = 5;
  kingdomCards[2] = 6;
  kingdomCards[3] = 0;
  for(i = 4; i<10; i++){
    kingdomCards[i] = i + 3;
  }
  randomSeed = 2;
  currentPlayer = 1;

  initializeGame(numPlayers, kingdomCards, randomSeed, &s);

  choice1 = 2;
  choice2 = 4;
  handPos = choice1;
  s.hand[currentPlayer][2] = province;

  i = mine_helper(choice1, choice2, &s, handPos);
  if(i > 0){
    printf("failed check choice < copper\n");
  }

  //test 2
  numPlayers = 3;
  kingdomCards[0] = 4;
  kingdomCards[1] = 5;
  kingdomCards[2] = 6;
  kingdomCards[3] = 0;
  for(i = 4; i<10; i++){
    kingdomCards[i] = i + 3;
  }
  randomSeed = 2;
  currentPlayer = 1;

  initializeGame(numPlayers, kingdomCards, randomSeed, &s);

  choice1 = 2;
  s.hand[currentPlayer][2] = adventurer;

  i = mine_helper(choice1, choice2, &s, handPos);
  if(i > 0){
    printf("failed check choice > gold\n");
  }

  //test 3
  numPlayers = 3;
  kingdomCards[0] = 4;
  kingdomCards[1] = 5;
  kingdomCards[2] = 6;
  kingdomCards[3] = 0;
  for(i = 4; i<10; i++){
    kingdomCards[i] = i + 3;
  }
  randomSeed = 2;
  currentPlayer = 1;

  initializeGame(numPlayers, kingdomCards, randomSeed, &s);

  choice1 = 3;
  choice2 = 2;
  s.hand[currentPlayer][2] = 27;

  i = mine_helper(choice1, choice2, &s, handPos);
  if(i > 0){
    printf("failed check choice > treasure_map\n");
  }

  //test 4
  numPlayers = 3;
  kingdomCards[0] = 4;
  kingdomCards[1] = 5;
  kingdomCards[2] = 6;
  kingdomCards[3] = 0;
  for(i = 4; i<10; i++){
    kingdomCards[i] = i + 3;
  }
  randomSeed = 2;
  currentPlayer = 1;

  initializeGame(numPlayers, kingdomCards, randomSeed, &s);

  choice1 = 5;
  choice2 = 2;
  s.hand[currentPlayer][2] = -1;

  i = mine_helper(choice1, choice2, &s, handPos);
  if(i > 0){
    printf("failed check choice < curse\n");
  }

  //test 5
  numPlayers = 3;
  kingdomCards[0] = 4;
  kingdomCards[1] = 5;
  kingdomCards[2] = 6;
  kingdomCards[3] = 0;
  for(i = 4; i<10; i++){
    kingdomCards[i] = i + 3;
  }
  randomSeed = 2;
  currentPlayer = 1;

  initializeGame(numPlayers, kingdomCards, randomSeed, &s);

  choice1 = 4;
  choice2 = 5;
  handPos = choice1;
  s.hand[currentPlayer][2] = province;

  i = mine_helper(choice1, choice2, &s, handPos);
  if(i < 0){
    printf("failed before getting card on valid input\n");
  }
 // if()

  return 0;
}

int mine_helper(int choice1, int choice2, struct gameState *state, int handPos){
     int currentPlayer = whoseTurn(state);
     int j = state->hand[currentPlayer][choice1];  //store card we will trash

     if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
     {
          return -1;
     }

     if (choice2 > treasure_map || choice2 < curse)
     {
          return -1;
     }

     if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
     {
          return -1;
     }

     gainCard(choice2, state, 2, currentPlayer);

     //discard card from hand
     discardCard(handPos, currentPlayer, state, 0);

     //discard trashed card
     for (int i = 0; i < state->handCount[currentPlayer]; i++)
     {
          if (state->hand[currentPlayer][i] == j)
          {
               discardCard(i, currentPlayer, state, 0);
               break;
          }
     }

     return 0;
}
