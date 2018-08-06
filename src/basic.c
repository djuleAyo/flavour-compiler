#include "basic.h"
#include "flavour.h"

basic_object make_int_object(int x)
{
  object o = malloc(sizeof(struct _object));
  assert(o);

  o->type_val = int_type;

  //WARNING: int is stored as is in void* - INT THE TAKEN PTR
  o->data = malloc(sizeof(int));
  assert(o->data);

  *(int*)(o->data) = x;

  return o;
}
basic_object make_string_object(string s)
{
  object o = malloc(sizeof(struct _object));
  assert(o);

  o->type_val = string_type;

  //WARNING: string dups given string!!!
  o->data = strdup(s);

  return o;
}


basic_object clone_int_object(object o)
{
  return make_int_object(*(int*)(o->data));
}

basic_object clone_string_object(object o)
{
  return make_string_object((string)(o->data));
}


void free_int_object(object o)
{
  free(o->data);
  free(o);
}
void free_string_object(object o)
{
  free(o->data);
  free(o);
}


#define MAX_NUM_LEN 15
string int_object_to_string(object o) {
  assert((o->type_val->node_type == TYPE_BASIC_NODE)
         && (o->type_val->node.basic_node->type ==
             BASIC_TYPE_INT));

  string ret_str = malloc(MAX_NUM_LEN);
  assert(ret_str);

  sprintf(ret_str, "%d", *(int*)(o->data));

  return ret_str;

}
#undef MAX_NUM_LEN

string string_object_to_string(object o) {
  assert((o->type_val->node_type == TYPE_BASIC_NODE)
         && (o->type_val->node.basic_node->type ==
             BASIC_TYPE_STRING));

  string ret_str = malloc(strlen(o->data) + 3);
  assert(ret_str);

  sprintf(ret_str, "\"%s\"", (char*)(o->data));
  return ret_str;

}
