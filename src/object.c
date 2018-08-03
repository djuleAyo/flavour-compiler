#include "object.h"
#include "flavour.h"

void free_object(object o)
{
  free(o->data);
  free(o);
}

object make_object(type t, list arguments) {
  object new = malloc(sizeof(struct _object));
  assert(new);

  new->type_val = t;

  if(!strcmp(t->name, "int") || !strcmp(t->name, "string")) {
    if(t->node.basic_node->type == BASIC_TYPE_INT)
      {
        new->data = malloc(sizeof(int));
        *(int*)(new->data) = *(int*)(arguments->data);
      }
    else
      {
        new->data = (string)(arguments->data);
      }
    return new;
  }

  void* value = object_initialize(t, arguments);

  new->data = value;

  return new;
}


void* object_initialize(type t, list arguments)
{

  void *obj_val;

  type tmp;
  obj_val = fv_alloc(t);
  int i  = 0;
  list_node iterator = arguments;

  while((tmp = get_ith_leaf(t, i)))
    {

      memcpy((((char*)obj_val)+tmp->offset), ((object)(iterator->data))->data, sizeof(void*));

      iterator = iterator->next;
      i++;
    }

  return obj_val;
}
