#ifndef _LIST_H
#define _LIST_H

#include "flavour.h"

struct _list
{
  void* data;
  struct _list* next;
};
typedef struct _list* list;
typedef list list_node;

void free_list(list* l);
list make_list();

//callback funcs
typedef bool(*equals_cb)(void* v1, void* v2);

//operations over list change list head;
//send list adress so it can be saved implcitly

//list functions return data sent/found in list node
void* list_add_end(list* l, void* v);
void* list_add_start(list* l, void* v);

void* list_find(list l, void* v, equals_cb e);
void* list_remove(list* l, void* v, equals_cb e);
void list_iterate(list l, void(*cb)(void *));


#endif
