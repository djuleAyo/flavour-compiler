#ifndef _TYPE_H
#define _TYPE_H
#include "flavour.h"

struct _type;
typedef struct _type* type;

typedef enum {
  BASIC_TYPE_INT,
  BASIC_TYPE_STRING,
} basic_types_enum;

typedef enum {
  TYPE_BASIC_NODE,
  TYPE_COMPOSITE_NODE,
  TYPE_FUNCTION_NODE
} type_node_type;

//==============================================================================

//type is tree of given type. every struct of the tree has type prefix
struct _type_basic_node {
  basic_types_enum type;
};
typedef struct _type_basic_node* type_basic_node;

type make_type_basic_node(basic_types_enum t, string propertie);
void free_type_basic_node(type_basic_node n);
//==============================================================================

//if volume is 1 make it 10. 1 is set for testing - to test reallocs
#define INITIAL_COMPOSITE_NODE_VOLUME 1
struct _type_composite_node {
  unsigned volume;
  unsigned size;
  type* nodes;
};
typedef struct _type_composite_node* type_composite_node;

type make_type_composite_node(string name, string propertie);
void free_type_composite_node(type_composite_node n);

void add_node_to_composite(type_composite_node comp, type node);

//==============================================================================
struct _type_function_node {
  type return_type;
  type arguments;
};

typedef struct _type_function_node* type_function_node;

type make_type_function_node(type rt, type args);
void free_type_function_node(type_function_node n);

//==============================================================================

struct _type {
  bool offset_initialized;
  string name;
  string propertie;
  unsigned offset;
  type_node_type node_type;
  union {
    type_basic_node basic_node;
    type_composite_node composite_node;
    type_function_node function_node;
  } node;
};



type make_type(string name, string propertie);
void free_type(type t);
string type_to_string(type t);

unsigned operator_sizeof(type t);
unsigned operator_dot(type t, string propertie);

type get_ith_leaf(type t,int i);

void* fv_alloc(type t);

/*
  type koren;

  switch (koren->node_type) {
  case node_type == TYPE_BASIC_NODE:
  print koren->node.basic_node->type
  }

 */

#endif
