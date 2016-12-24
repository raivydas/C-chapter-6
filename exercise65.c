// This is the solution to exercise 6.5 from K&R book.
// The function install takes two arguments and stores them in the hashtable. The first argument is a name and the second is its definition.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np;
  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else
    free((void *) np->defn);
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

void printtable() {
  int i;
  struct nlist *localptr;

  for (i  = 0; i < HASHSIZE; i++) {
    for (localptr = hashtab[i]; localptr != NULL; localptr = localptr->next)
      printf("%s %s\n", localptr->name, localptr->defn);
  }
}

void undef(char *name) {
  unsigned i = hash(name);
  struct nlist *np1;
  struct nlist *np2;

  for (np1 = hashtab[i]; np1 != NULL; np2 = np1, np1 = np1->next) {
    if (strcmp(np1->name, name) == 0) {
      if (np1 == hashtab[i]) {
        free(np1);
        hashtab[i] = NULL;
      } else {
        np2->next = np1->next;
        free(np1);
      }
      return;
    }
  }
}

int main(int argc, char const *argv[]) {
  char *name = "Raivydas";
  char *defn = "Simenas";

  install(name, defn);
  undef(name);
  printtable();
  printf("first check point\n");
  install(name, defn);
  printtable();
  return 0;
}
