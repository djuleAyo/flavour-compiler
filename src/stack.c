#include "stack.h"
#include "flavour.h"

stack make_stack()
{
  stack new = malloc(sizeof(struct _stack));
  assert(new);

  new->volume = STACK_INITIAL_VOLUME;
  new->size = 0;
  new->data = malloc(sizeof(void*) * STACK_INITIAL_VOLUME);
  assert(new->data);

  return new;
}
stack shrink_stack(stack s)
{
  s->volume /= 2;
  #ifdef STACK_TEST
  printf("shrinking volume: %d size: %d\n", s->volume, s->size);
  #endif
    
  s->data = realloc(s->data, s->volume * sizeof(void*));
  assert(s->data);
  return s;
}
stack expand_stack(stack s)
{
  s->volume *= 2;

  #ifdef STACK_TEST
  printf("expanding volume: %d size: %d\n", s->volume, s->size);
  #endif
  
  s->data = realloc(s->data, s->volume * sizeof(void*));
  assert(s->data);

  return s;
}


stack stack_push(stack s, void* ptr)
{
  #ifdef STACK_TEST
  printf("before push volume: %d size: %d\n", s->volume, s->size);
  #endif

  if(s->size == s->volume)
    expand_stack(s);

  (s->data)[s->size] = ptr;
  s->size++;

  return s;
}
void* stack_pop(stack s)
{
    if(s->size == 0)
        return NULL;
  void* ptr = (s->data)[s->size - 1];
  s->size--;

  if(s->size < s->volume / 2 && s->volume > STACK_INITIAL_VOLUME)
    s = shrink_stack(s);
  
  return ptr;
}

void* stack_top(stack s)
{
    if(s->size == 0)
        return NULL;
  return (s->data)[s->size - 1];
}

void print_stack(stack s, void (*print_callback)(void*))
{
  printf("Steka od %d elemenata\n", s->size);
  printf("------------------------------------------\n");
  for(int i = s->size - 1; i >= 0; i--) {
    print_callback((s->data)[i]);
    printf("\n");
  }
  if(!s->size)
    printf("Prazan stack\n");
  printf("------------------------------------------\n");
  
}

//everything stack holds MUST be unallocated before a stack is.
void free_stack(stack s)
{
  free(s->data);
  free(s);
}


