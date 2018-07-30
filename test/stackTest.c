#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void stampaj_int(void* x)
{
  printf("%d ", *(int*)x);
}

#define TEST_SIZE 100

int main()
{
  
  printf("size of void* %d\n", (int)sizeof(void*));
  stack s = Stack();

  int x = 3;

  for(int i = 0; i < TEST_SIZE; i++) {
    push(s, &x);
  }
  
  print_stack(s, stampaj_int);
  
  
  for(int i = 0; i < TEST_SIZE; i++) {
    pop(s);
  }
  
  print_stack(s, stampaj_int);
  
  free_stack(s);

  return 0;
}
