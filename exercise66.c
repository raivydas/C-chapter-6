// The program implements a simple #define preprocessor. For example, the user has to input the following line: #define name John. This line stores an entry in the hashtable where the key is "name" and the value is "John".

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TABLE_LENGTH 50
#define WORD_LENGTH 15

struct tnode {
  struct tnode *next;
  char name[WORD_LENGTH];
  char defn[WORD_LENGTH];
};

struct tnode *hashtab[TABLE_LENGTH];

int stored_char = '\0';


void inithashtab() {
  int i;

  for (i = 0; i < TABLE_LENGTH; i++)
    *hashtab = NULL;
}


void initnode(struct tnode *nodetoinit, char *name, char *defn) {
  nodetoinit->next = NULL;
  strcpy(nodetoinit->name, name);
  strcpy(nodetoinit->defn, defn);
}


int getch() {
  if (stored_char == '\0')
    return getchar();
  else {
    int char_to_return = stored_char;
    stored_char = '\0';
    return char_to_return;
  }
}


void ungetch(int c) {
  stored_char = c;
}


int getword(char *word) {
  char w[WORD_LENGTH];
  int lim = WORD_LENGTH;
  int curr_char;
  int wp = 0;

  while(!isalnum(curr_char = getch()) && curr_char != EOF)
    ;

  if (curr_char == EOF)
    return 1;

  if (isalnum(curr_char))
    ungetch(curr_char);

  while(isalnum(curr_char = getch()) && --lim > 0)
    w[wp++] = curr_char;

  w[wp] = '\0';

  strcpy(word, w);

  return 0;
}


unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % TABLE_LENGTH;
}


void insert(struct tnode *nodetoinsert) {
  unsigned hashval = hash(nodetoinsert->name);
  struct tnode *currnode = hashtab[hashval];
  struct tnode *prevnode = hashtab[hashval];

  while (currnode != NULL) {
    prevnode = currnode;
    currnode = currnode->next;
  }

  if (currnode == hashtab[hashval])
    hashtab[hashval] = nodetoinsert;
  else
    prevnode->next = nodetoinsert;
}


void insertdefineline() {
  struct tnode *currnode = (struct tnode *) malloc(sizeof(struct tnode));
  char currword[WORD_LENGTH];

  if (getchar() != '#')
    return;

  getword(currword);

  if (strcmp(currword, "define") == 0) {
    char currname[WORD_LENGTH];
    char currdefn[WORD_LENGTH];

    if (getword(currname) == 0 && getword(currdefn) == 0) {
      initnode(currnode, currname, currdefn);
      insert(currnode);
    }
  }
}


void printhashtable() {
  int i;
  struct tnode *currnode;

  for(i = 0; i < TABLE_LENGTH; i++) {
    currnode = hashtab[i];
    while (currnode != NULL) {
      printf("%s %s\n", currnode->name, currnode->defn);
      currnode = currnode->next;
    }
  }
}


int main(int argc, char const *argv[]) {
  inithashtab();

  insertdefineline();

  printhashtable();

  return 0;
}
