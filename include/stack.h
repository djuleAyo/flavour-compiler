#pragma once

#define STACK_INITIAL_VOLUME (1 << 0)
//Since stack does not know what it holds it cannot free anything
//The user of the stack is responsible for dealloc.

struct _stack {
  int volume;
  int size;
  //array holds ptrs to anything (void*)
  void** data;
};
typedef struct _stack* stack;

stack Stack();
stack push(stack s, void* ptr); //begin scope
void* pop(stack s); //end scope
/*shrink_stack and expand_stack
 *are private functions*/
//stack shrink_stack(stack s);
//stack expand_stack(stack s);
void* top(stack s);
void print_stack(stack s, void (*print_callback)(void*));
void free_stack(stack s);
