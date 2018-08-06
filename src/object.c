#include "object.h"
#include "flavour.h"

void free_object(object o)
{
  switch(o->type_val->node_type) {
  case TYPE_BASIC_NODE:
    switch(o->type_val->node.basic_node->type) {
    case BASIC_TYPE_INT:
      free_int_object(o);
      break;
    case BASIC_TYPE_STRING:
      free_string_object(o);
      break;

    }
    break;
  case TYPE_FUNCTION_NODE:
    free_lambda(o);
    break;
  case TYPE_COMPOSITE_NODE:
    free_struct(o);
    break;
  case TYPE_TYPE_NODE:
    break;
  }
}


string object_to_string(object o){
  switch(o->type_val->node_type) {
  case TYPE_BASIC_NODE:
    switch(o->type_val->node.basic_node->type) {
    case BASIC_TYPE_INT:
      return int_object_to_string(o);
      break;
    case BASIC_TYPE_STRING:
      return string_object_to_string(o);
      break;
    }
    break;
  case TYPE_COMPOSITE_NODE:

    break;
  case TYPE_FUNCTION_NODE:

    break;
  case TYPE_TYPE_NODE:

    break;
  }
  return NULL;
}

object clone_object(object o)
{
  object ret_val = NULL;
  switch(o->type_val->node_type)
    {
    case TYPE_BASIC_NODE:
      switch(o->type_val->node.basic_node->type)
        {
        case BASIC_TYPE_INT:
          ret_val = clone_int_object(o);
          break;
        case BASIC_TYPE_STRING:
          ret_val = clone_string_object(o);
          break;
        }
      break;
    case TYPE_FUNCTION_NODE:
      ret_val = clone_lambda(o);
      break;
    case TYPE_COMPOSITE_NODE:
      ret_val = clone_struct(o);
      break;
    case TYPE_TYPE_NODE:

      break;
    }
  return ret_val;
}
