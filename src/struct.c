#include "struct.h"
#include "flavour.h"




void free_struct(struct_object o)
{
  //TODO napisati lepo funkciju
  free(o->data);
}

object operator_dot(struct_object o, string propertie) {

  object new = malloc(sizeof(struct _object));
  assert(new);

  assert(o->type_val->node_type == TYPE_COMPOSITE_NODE
         && "Using operator dot on an object that is not of composite type\n");

  for(unsigned i = 0; i < o->type_val->node.composite_node->size; i++) {
    if(!strcmp((o->type_val->node.composite_node->nodes)[i]->propertie,
               propertie)) {
      new->type_val = (o->type_val->node.composite_node->nodes)[i];
      break;
    }
  }

  new->data = (char*)(o->data) + new->type_val->offset;
  return new;
}
object make_struct(type t, list arguments)
{
  void *obj_val;

  type tmp;
  obj_val = fv_alloc(t);

  unsigned total_offset = 0;

  int i  = 0;
  list_node iterator = arguments;
  while((tmp = get_ith_leaf(t, i)))
    {

      memcpy((((char*)obj_val) + total_offset + tmp->offset),
             iterator->data,
             operator_sizeof(tmp));

      iterator = iterator->next;

      total_offset += operator_sizeof(tmp);
      i++;
    }


  object new = malloc(sizeof(struct _object));
  assert(new);

  new->type_val = t;
  new->data = obj_val;
  return new;
}

struct_object clone_struct(struct_object o)
{
  //TODO uradi ovo sramoto
  UNUSED(o);
  return NULL;

}
