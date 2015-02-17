#include <stdio.h>
#include <stdlib.h>

int woof()
{
  fprintf(stderr, "enter woof, even though no one calls me...\n");
  exit(0);
}

int
bar(int x)
{
  int barray[0];
  int i;
  register int *sp asm("esp");
  fprintf(stderr, "Stack pointer is %p\n", sp);

  fprintf(stderr,"enter bar\n");
  for (i = 0; i < 6; i++) {
    fprintf(stderr,"barray[%d] = 0x%x\n", i, barray[i]);
  }
  barray[4] = (int) woof;
  fprintf(stderr,"exit bar, barray[%d] is %x\n", i, barray[i]);
}


int
foo(int n)
{
  int farray[0];
  int i;

  fprintf(stderr,"enter foo(%d)\n", n);
  register int *sp asm("esp");
  fprintf(stderr, "Stack pointer is %p\n", sp);

  for (i = 0; i < 6; i++) {
    fprintf(stderr,"Farray[%d] = 0x%x\n", i, farray[i]);
  }

  if (n < 1) {
    bar(0);
  } else {
    foo(n-1);
  }
  fprintf(stderr,"leave foo(%d)\n", n);
}

int
main(int argc, char *argv[])
{
  register int *sp asm("esp");
  fprintf(stderr, "enter main\n");
  fprintf(stderr, "Stack pointer is %p\n", sp);

  fprintf(stderr, "&main = 0x%p\n", &main);
  fprintf(stderr, "&foo = 0x%p\n", &foo);
  fprintf(stderr, "&bar = 0x%p\n", &bar);
  fprintf(stderr, "&woof = 0x%p\n", &woof);
  

  foo(2);
}
