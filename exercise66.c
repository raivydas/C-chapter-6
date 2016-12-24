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

char *getword() {
  char word[MAXLEN];
  int currp = 0;
  char currchar;
  while ((currchar = getch()) != EOF && isalnum(currchar) && currp < MAXLEN)
    word[currp++] = currchar;
  while (!isalnum(currchar = getch()))
    ;
  if (isalnum(currchar))
    ungetch(currchar);
  word[currp] = '\0';
  return word;
}

int main(int argc, char const *argv[]) {
  char *word;
  char c;
  word = malloc(MAXLEN*(sizeof(char)));
  word = getword();
  printf("%s\n", word);
  return 0;
}
