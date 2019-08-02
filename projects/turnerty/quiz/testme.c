#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    //ascii 32 - 126
    int r = rand() % (126 - 32 + 1) + 32;
    char c = (char) r;
    return c;
}

char *inputString(char *s)
{
    // TODO: rewrite this function
    //char s[10];
    int i = 0;
    int len = rand() % 20 - 1 + 1 + 1;

    for(i=0; i<len; i++){
      s[i] = (int) (rand() % (126 - 32 + 1) + 32);
    }

    s[len] = '\0';

    i = rand() % 10000000;
    if(i == 391387){
      s[0] = 'r';
      s[1] = 'e';
      s[2] = 's';
      s[3] = 'e';
      s[4] = 't';
      s[5] = '\0';
    }
    return s;
}

void testme()
{
  int tcCount = 0;
  char s[21];
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    inputString(s);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
