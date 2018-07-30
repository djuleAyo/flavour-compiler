#ifndef _STACK_H
#define _STACK_H
/* module description - this is generic stack */

/* interface description - holds usual stack interface.
 * Implementation is based on void ptrs.
 * No struct knows its own type hence
 * user must menage memory for stored objects.
 */

#define STACK_INITIAL_VOLUME (1 << 4)

struct _stack {
  int volume;
  int size;
  //implemented by array of void ptrs
  void** data;
};
typedef struct _stack* stack;

stack make_stack();
void free_stack(stack s);

/* Stack can menage its own size and volume
 * no need for out of bounds checking
 */
stack stack_push(stack s, void* ptr); //begin scope
void* stack_pop(stack s); //end scope
void* stack_top(stack s);
void print_stack(stack s, void (*print_callback)(void*));

#endif
