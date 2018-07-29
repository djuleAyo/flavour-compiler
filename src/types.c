#include "types.h"


basic_type_value Basic_type_value(type_enum t, void* v)
{
  basic_type_value b = malloc(sizeof(struct _basic_type_value));
  assert(b);

  b->type = t;
  switch(t) {
  case TYPE_ENUM_INT:
    b->var.num = *(int*)v;
    break;

  case TYPE_ENUM_STRING:
    b->var.str = (string)v;
    break;

  default:
    assert(0);
  }
  return b;
}
