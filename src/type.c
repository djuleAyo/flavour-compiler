#include "type.h"

type make_type_basic_node(basic_types_enum t, string propertie)
{
  type_basic_node new = malloc(sizeof(struct _type_basic_node));
  assert(new);

  new->type = t;

  type wrapper = make_type(t == BASIC_TYPE_INT ? "int" : "string", propertie);
  wrapper->node_type = TYPE_BASIC_NODE;
  wrapper->node.basic_node = new;
  return wrapper;
}
void free_type_basic_node(type_basic_node n)
{
  free(n);
}

type make_type_composite_node(string name, string propertie)
{
  type_composite_node new = malloc(sizeof(struct _type_composite_node));
  assert(new);

  new->size = 0;
  new->volume = INITIAL_COMPOSITE_NODE_VOLUME;
  new->nodes = malloc(sizeof(type) * INITIAL_COMPOSITE_NODE_VOLUME);
  assert (new->nodes);

  type wrapper = make_type(name, propertie);
  wrapper->node_type = TYPE_COMPOSITE_NODE;
  wrapper->node.composite_node = new;

  return wrapper;
}
void add_node_to_composite(type_composite_node comp, type node)
{
  if(comp->size == comp->volume) {
    comp->volume *= 2;
    comp->nodes = realloc(comp->nodes, sizeof(type) * comp->volume);
    assert(comp->nodes);
  }

  (comp->nodes)[comp->size++] = node;
}
void free_type_composite_node(type_composite_node n)
{
  for(unsigned i = 0; i < n->size; i++) {
    free_type((n->nodes)[i]);
  }
  free(n->nodes);
  free(n);
}

type make_type(string name, string propertie)
{
  type t = malloc(sizeof(struct _type));
  assert(t);
  t->offset_initialized = false;
  t->name = strdup(name);
  t->propertie = propertie ? strdup(propertie) : NULL;

  return t;
}
void free_type(type t)
{
  switch(t->node_type) {
  case TYPE_BASIC_NODE:
    free_type_basic_node(t->node.basic_node);
    break;
  case TYPE_COMPOSITE_NODE:
    free_type_composite_node(t->node.composite_node);
    break;
  }
  free(t->name);
  free(t->propertie);
  free(t);
}


//unopt implementation

string type_to_string(type t)
{
  //recursion exit
  if(t->node_type == TYPE_BASIC_NODE) {
    string type_name;
    switch(t->node.basic_node->type) {
    case BASIC_TYPE_INT:
      type_name = strdup("int");
      break;
    case BASIC_TYPE_STRING:
      type_name =  strdup("string");
      break;
    }
    if(!(t->propertie)) return type_name;

    string ret_str = malloc(strlen(type_name) + 3 + strlen(t->propertie));
    sprintf(ret_str, "%s %s;", type_name, t->propertie);

    free(type_name);

    return ret_str;
  }

  unsigned num_of_children = t->node.composite_node->size;

  string* child_str_array = malloc(sizeof(string) * num_of_children);
  assert(child_str_array);

  int total = 0;
  for(unsigned i = 0; i < num_of_children; i++) {
    child_str_array[i]
      = type_to_string((t->node.composite_node->nodes)[i]);
    total += strlen(child_str_array[i]);
  }

  total += strlen(t->name);

  //separators are \s so there are num_of_children - 1 of them
  //outer { } are 2 extra chars
  //and \0 at end
  int aditional_chars = num_of_children + 2 + 1;

  string ret_str = malloc(total + aditional_chars + 2);
  assert(ret_str);

  int offset = sprintf(ret_str, "%s", t->name);
  offset += sprintf(ret_str + offset, "{");
  for(unsigned i = 0; i < num_of_children; i++) {
    offset += sprintf(ret_str + offset, "%s ", child_str_array[i]);
    free(child_str_array[i]);
  }
  sprintf(ret_str + offset, "}");
  free(child_str_array);

  return ret_str;

}


unsigned operator_dot(type t, string propertie)
{
  if(t->node_type != TYPE_COMPOSITE_NODE)
    assert(!E_TYPE_ACCESS);
  if(!t->offset_initialized)
    {
      operator_sizeof(t);
    }
  for(unsigned i = 0; i < t->node.composite_node->size; i++)
    {
      if(!strcmp((t->node.composite_node->nodes)[i]->propertie, propertie))
        {
          return (t->node.composite_node->nodes)[i]->offset;
        }
    }
  assert(!E_TYPE_ACCESS);
}

unsigned operator_sizeof(type t)
{
  if(t->node_type == TYPE_BASIC_NODE)
    switch(t->node.basic_node->type) {
    case BASIC_TYPE_INT:
      return sizeof(int);
    case BASIC_TYPE_STRING:
      return sizeof(string);
    default:
      assert(E_TYPE_ACCESS);
      //to shut gcc warning control reaches...
      return 0;
    }
  else {
    unsigned summ = 0;
    for(unsigned i = 0; i < t->node.composite_node->size; i++) {
      (t->node.composite_node->nodes)[i]->offset = summ;
      summ += operator_sizeof((t->node.composite_node->nodes)[i]);
    }
    t->offset_initialized = true;
    return summ;
  }
}


void* fv_alloc(type t)
{
  void *tmp = malloc(operator_sizeof(t));
  assert(tmp);
  return tmp;
}


//TODO napraviti za user defined tipove

/* if ptr is NULL no memory will be allocated and
   default constructor will */



type _get_ith_leaf(type t, int i, int* j)
{
  if(t->node_type == TYPE_BASIC_NODE)
    {
      if(*j == i)
        return t;
      else
        {
          *j += 1;
          return NULL;
        }

    }
  else
    {
      unsigned k;
      type ret_type;
      for(k=0; k < t->node.composite_node->size; k++)
        {
          if((ret_type = _get_ith_leaf((t->node.composite_node->nodes)[k], i,j)))
            return ret_type;

        }
    }
  return NULL;
}

type get_ith_leaf(type t,int i)
{
  int j=0;
  return _get_ith_leaf(t,i,&j);

}
