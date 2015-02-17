#include <stdio.h>

int add(int a, int b)
{
  return a + b;
}

int ptrAdd(int *ptrA, int *ptrB)
{
  return *ptrA + *ptrB;
  
}

int globalA;
int globalB;
int globalResult;

int main()
{
  int localA = 8;
  int localB = 20;

  globalResult = add(5,10);

  globalA = 50;
  globalB = 100;
  globalResult = ptrAdd(&globalA, &globalB);

  globalResult = ptrAdd(&localA, &localB);

  printf("Result is %d\n", globalResult);

  return 0;
}
