#include "list.h"

list_node make_list_node(void* v);
void free_list_node(list_node n);


void free_list(list* l)
{
  list_node iterator = *l;
  list_node tmp;
  while(iterator) {
    tmp = iterator->next;
    free_list_node(iterator);
    iterator = tmp;
  }
  *l = NULL;
}
void free_list_node(list_node n)
{
  free(n);
}
list make_list()
{
  return NULL;
}
list_node make_list_node(void* v) {
  list_node new = malloc(sizeof(struct _list));
  assert(new);

  new->next = NULL;
  new->data = v;

  return new;
}

void* list_add_end(list* l, void* v)
{
  if(!(*l)) {
    return list_add_start(l, v);
  }

  list_node tmp = *l;
  while(tmp->next)
    tmp = tmp->next;

  tmp->next = make_list_node(v);

  return v;
}
void* list_add_start(list* l, void* v)
{
  list_node new = make_list_node(v);

  new->next = *l;

  *l = new;

  return v;
}

void* list_find(list l, void* v, equals_cb e)
{
  if(!l) return NULL;

  list_node tmp = l;
  while(tmp) {
    if(e(tmp->data, v)) return tmp->data;
    tmp = tmp->next;
  }
  return NULL;
}
void* list_remove(list* l, void* v, equals_cb e)
{
  if(!(*l)) return NULL;

  if(e((*l)->data, v)) {
    list_node tmp = (*l)->next;
    void* ret_val = (*l)->data;
    free_list_node(*l);
    *l = tmp;
    return ret_val;
  }

  list_node iterator = *l;

  while(iterator->next) {
    if(e(iterator->next->data, v)) {
      list_node tmp = iterator->next;
      void* ret_val = tmp->data;
      iterator->next = iterator->next->next;
      free_list_node(tmp);
      return ret_val;
    }
    iterator = iterator->next;
  }
  return NULL;
}


void list_iterate(list l, void(*cb)(void *))
{
    list_node tmp = l;
    while(tmp)
    {
        cb(tmp->data);
        tmp = tmp->next;
    }
}




















