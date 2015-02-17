#include <stdio.h>
#include <stdlib.h>

struct CharIntChar {
	char c;
	int i;
	char q;
};

struct CharCharInt {
	char c;
	char q;
	int i;
};

struct IntIntInt {
	int c;
	int i;
	int q;
  struct IntIntInt *ptr;
};

struct CharIntChar woof;
struct CharCharInt woof2;
struct IntIntInt woof3;

int intArray[10];
struct CharIntChar charIntCharArray[10];

struct IntIntInt *head = NULL;

void pause(char *msg) { fprintf(stdout, msg); }

int
main(int argc, char **agrgv)
{
  int i;

  /////////////////////////////////////////////////////////////////////////
  // Structure
  /////////////////////////////////////////////////////////////////////////

  fprintf(stdout, "---- structures ----\n");

  woof.c = 1;
  woof.i = 2;
  woof.q = 3;
  fprintf(stdout, "sizeof woof is %d\n", sizeof(woof));

  woof2.c = 1;
  woof2.i = 2;
  woof2.q = 3;
  fprintf(stdout, "sizeof woof2 is %d\n", sizeof(woof2));
	  
   pause("Now, pause to look at 'woof' and 'woof2'\n");

  /////////////////////////////////////////////////////////////////////////
  // Array
  /////////////////////////////////////////////////////////////////////////

  fprintf(stdout, "---- array ----\n");
  for (i = 0; i < 10; i++) {
    intArray[i] = i;
  }

  for (i = 0; i < 10; i++) {
    charIntCharArray[i].c = charIntCharArray[i].i = charIntCharArray[i].q = i;
  }
  
  pause( "Now, pause to look at 'intArray' and 'charIntCharArray'\n");


  /////////////////////////////////////////////////////////////////////////
  // Linked List
  /////////////////////////////////////////////////////////////////////////
  
  fprintf(stdout, "---- Linked list ----\n");
  //
  // Create a linked list, with a (repeatable) random allocation
  // of other objects to make certain they're not all
  // contiguous
  //
  srandom(3);

  for (i = 0; i < 10; i++) {
    //
    // Malloc a few random sizes...
    //
    int *randomData[10];
    int j;
    for (j = 0; j < 10; j++) {
      randomData[j] = malloc(random() % 100);
    }
    struct IntIntInt *p = malloc(sizeof(struct IntIntInt));
    p -> c = p -> i = p -> q = i;
    p -> ptr  = head;
    head = p;
    for (j = 0; j < 10; j++) {
      free(randomData[j]);
    }
  }

  
  pause( "Now, pause to look at 'head' and linked list\n");

	return 0;

}
