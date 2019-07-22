CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c $(CFLAGS)
	gcc -o unittest2 unittest2.c $(CFLAGS)
	gcc -o unittest3 unittest3.c $(CFLAGS)
	gcc -o unittest4 unittest4.c $(CFLAGS)
	gcc -o unittest5 unittest5.c $(CFLAGS)
	gcc -o cardtest1 cardtest1.c $(CFLAGS)
	gcc -o cardtest2 cardtest2.c $(CFLAGS)
	gcc -o cardtest3 cardtest3.c $(CFLAGS)
	gcc -o cardtest4 cardtest4.c $(CFLAGS)
	gcc -o cardtest5 cardtest5.c $(CFLAGS)
	./unittest1 &> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	./unittest2 >> unittestresults.out 2>&1
	gcov unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	./unittest3 >> unittestresults.out 2>&1
	gcov unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	./unittest4 >> unittestresults.out 2>&1
	gcov unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	./unittest5 >> unittestresults.out 2>&1
	gcov unittest5.c >> unittestresults.out
	cat unittest5.c.gcov >> unittestresults.out
	./cardtest1 >> unittestresults.out 2>&1
	gcov cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	./cardtest2 >> unittestresults.out 2>&1
	gcov cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	./cardtest3 >> unittestresults.out 2>&1
	gcov cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	./cardtest4 >> unittestresults.out 2>&1
	gcov cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	./cardtest5 >> unittestresults.out 2>&1
	gcov cardtest5.c >> unittestresults.out
	cat cardtest5.c.gcov >> unittestresults.out




all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
