#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char const *argv[]) {
  printf("Hello, world\n");
  return 0;
}
