// This is a solution to exercise 6.6 from K&R book.
// The program implements a simple #define processor.
//
// Author: Raivydas Šimėnas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define BUFSIZE 1000
#define MAXLEN 200

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

char buf[BUFSIZE];
int bufp = 0;

char getch() {
  if (bufp != 0)
    return buf[bufp--];
  else
    return getchar();
}

void ungetch(char c) {
  if (bufp < BUFSIZE)
    buf[bufp++] = c;
  else
    printf("The buffer is full.\n");
}

//I found the following function on Internet: http://cboard.cprogramming.com/c-programming/169208-getword-function.html. Here I give a slightly modified version.

int getword(char *word, int lim) {
  char *w = word;
  int c;

}

int main(int argc, char const *argv[]) {
  char *word;
  char c;
  word = malloc(MAXLEN*(sizeof(char)));
  word = getword();
  printf("%s\n", word);
  return 0;
}
