#include "type.h"

type int_type;
type string_type;

void init_basic_types()
{
  int_type = make_type_basic_node(BASIC_TYPE_INT, NULL);
  string_type = make_type_basic_node(BASIC_TYPE_STRING, NULL);
}

type clone_lambda_type(type t)
{
  assert(t->node_type == TYPE_FUNCTION_NODE);

  return make_type_function_node(t->node.function_node->return_type, t->node.function_node->arguments);
}

void deinit_basic_types()
{
  free_type(int_type);
  free_type(string_type);
}

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

type make_type_type_node()
{
  type t = make_type("type", NULL);

  t->node_type = TYPE_TYPE_NODE;
  //all union fields are ptrs so we will init ANY of them on NULL
  t->node.basic_node = NULL;

  return t;
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
void add_node_to_composite(type_composite_node comp, type node, string propertie)
{
  if(comp->size == comp->volume) {
    comp->volume *= 2;
    comp->nodes = realloc(comp->nodes, sizeof(type) * comp->volume);
    assert(comp->nodes);
  }

  (comp->nodes)[comp->size] = node;
  (comp->nodes)[comp->size++]->propertie = strdup(propertie);
}
void free_type_composite_node(type_composite_node n)
{
  /* for(unsigned i = 0; i < n->size; i++) { */
  /*   free_type((n->nodes)[i]); */
  /* } */
  free(n->nodes);
  free(n);
}

type make_type_function_node(type rt, type args)
{
  type_function_node new = malloc(sizeof(struct _type_function_node));
  assert(new);

  type wrapper;

  new->return_type = rt;
  new->arguments = args;

  string type_name = NULL;
  string rt_str =  rt->name;

  //no arguments
  if(!args) {
    type_name = malloc(strlen(rt_str) + 4);
    assert(type_name);
    sprintf(type_name, "%s ()", rt_str);
    goto exit;
  }

  //1 arg
  if(args->name) {
    //4 additional chars: 2 for (), 1 for \0, 1 for \s
    type_name = malloc(strlen(rt_str) + strlen(args->name) + 4);
    assert(type_name);
    sprintf(type_name, "%s (%s)", rt_str, args->name);

    goto exit;
  }

  //argument list
  unsigned size = 0;
  for( unsigned i = 0; i < args->node.composite_node->size; i++) {
    size += strlen((args->node.composite_node->nodes)[i]->name) + 2;
  }
  type_name = malloc(size + strlen(rt_str) + 4);
  assert(type_name);

  unsigned offset
    = sprintf(type_name, "%s (%s", rt_str,
              (args->node.composite_node->nodes)[0]->name);

  for(unsigned i = 1; i < args->node.composite_node->size; i++) {
    offset += sprintf(type_name + offset, ", %s",
                      (args->node.composite_node->nodes)[i]->name);
  }
  sprintf(type_name + offset, ")");

 exit:
  wrapper = make_type(type_name, NULL);
  wrapper->node_type = TYPE_FUNCTION_NODE;
  wrapper->node.function_node = new;

  free(type_name);
  return wrapper;
}

void free_type_function_node(type_function_node n)
{
  /* free_type(n->return_type); */
  /* if(n->arguments) */
  /*     free_type(n->arguments); */
  free(n);
}

type make_type(string name, string propertie)
{
  type t = malloc(sizeof(struct _type));
  assert(t);
  t->offset_initialized = false;
  t->name = name? strdup(name):NULL;
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
  case TYPE_FUNCTION_NODE:
    free_type_function_node(t->node.function_node);
    break;
  case TYPE_TYPE_NODE:
    //nothing to be done
    break;
  }
  free(t->name);
  free(t->propertie);
  free(t);
}


//unopt implementation

string type_to_string(type t)
{
  //return string composed of type_name and if type is propertie of a structure
  //then append propetie name
  string type_name;

  switch(t->node_type) {
  case TYPE_BASIC_NODE:
    goto basic;
    break;
  case TYPE_COMPOSITE_NODE:
    goto composite;
    break;
  case TYPE_FUNCTION_NODE:
    goto function;
    break;
  case TYPE_TYPE_NODE:
    goto type;
    break;
  }

 basic:
  switch(t->node.basic_node->type) {
  case BASIC_TYPE_INT:
    type_name = strdup("int");
    break;
  case BASIC_TYPE_STRING:
    type_name =  strdup("string");
    break;
  }
  goto exit;

 type:
  type_name = strdup("type");
  goto exit;

 function:
  type_name = strdup(t->name);

  goto exit;


 composite: {
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

    type_name = malloc(total + aditional_chars + 2);
    assert(type_name);

    int offset = sprintf(type_name, "%s", t->name);
    offset += sprintf(type_name + offset, "{");
    for(unsigned i = 0; i < num_of_children; i++) {
      offset += sprintf(type_name + offset, "%s ", child_str_array[i]);
      free(child_str_array[i]);
    }
    sprintf(type_name + offset, "}");
    free(child_str_array);
  }

 exit: {
    if(!(t->propertie)) return type_name;

    string ret_str = malloc(strlen(type_name) + 3 + strlen(t->propertie));
    sprintf(ret_str, "%s %s;", type_name, t->propertie);

    free(type_name);

    return ret_str;
  }

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


bool type_equals(type t1, type t2)
{
  if(t1->node_type != t2->node_type)
    return false;
  switch(t1->node_type)
    {
    case TYPE_BASIC_NODE:
      {
        if(t1->node.basic_node->type != t2->node.basic_node->type)
          return false;
        else
          return true;
      }
      break;
    case TYPE_FUNCTION_NODE:
      {
        if((type_equals(t1->node.function_node->return_type, t2->node.function_node->return_type)==true)
           && (type_equals(t1->node.function_node->arguments, t2->node.function_node->arguments)==true))
          return true;
        else
          return false;
      }
      break;
    case TYPE_COMPOSITE_NODE:
      {
        if(t1->node.composite_node->size != t2->node.composite_node->size)
          return false;
        if(t1->name && t2->name) {
          if(strcmp(t1->name, t2->name))
            return false;
          else
            return true;
        }

        unsigned i;
        bool ret = false;
        for(i=0; i < t1->node.composite_node->size; i++)
          {
            ret = type_equals((t1->node.composite_node->nodes)[i], (t2->node.composite_node->nodes)[i]);
            if(!ret)
              return false;
          }

        return true;
      }
      break;
    default:
      assert(!E_WRONG_TYPE);
    }
}
