CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	- ./testme &> randomtest.out
	gcov testme.c -b >> randomtest.out
	cat testme.c.gcov >> randomtest.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out
