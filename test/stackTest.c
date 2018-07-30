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
  stack s = make_stack();

  int x = 3;

  for(int i = 0; i < TEST_SIZE; i++) {
    stack_push(s, &x);
  }
  
  print_stack(s, stampaj_int);
  
  printf("stack top:%d\n",*(int*)stack_top(s));
  
  
  for(int i = 0; i < TEST_SIZE; i++) {
    stack_pop(s);
  }
  
  int *n = stack_top(s);
  printf("stack top %s\n", n?"ima":"nema");
  
  
  print_stack(s, stampaj_int);
  
  free_stack(s);

  return 0;
}
