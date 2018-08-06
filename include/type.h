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
  TYPE_FUNCTION_NODE,
  TYPE_TYPE_NODE,

} type_node_type;


//USE THIS EVERY TIME WHEN USING BASIC TYPES
extern type int_type;
extern type string_type;
void init_basic_types();
void deinit_basic_types();

//==============================================================================

//type is tree of given type. every struct of the tree has type prefix
struct _type_basic_node {
  basic_types_enum type;
};
typedef struct _type_basic_node* type_basic_node;

type make_type_basic_node(basic_types_enum t, string propertie);
void free_type_basic_node(type_basic_node n);
//==============================================================================
type make_type_type_node();
//==============================================================================

//if volume is 1 make it 10. 1 is set for testing - to test reallocs
#define INITIAL_COMPOSITE_NODE_VOLUME 10
struct _type_composite_node {
  unsigned volume;
  unsigned size;
  type* nodes;
};
typedef struct _type_composite_node* type_composite_node;

type make_type_composite_node(string name, string propertie);
void free_type_composite_node(type_composite_node n);

void add_node_to_composite(type_composite_node comp, type node, string propertie);

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
type clone_lambda_type(type t);

string type_to_string(type t);

unsigned operator_sizeof(type t);

type get_ith_leaf(type t,int i);


void* fv_alloc(type t);

bool type_equals(type t1, type t2);

/*
  type koren;

  switch (koren->node_type) {
  case node_type == TYPE_BASIC_NODE:
  print koren->node.basic_node->type
  }

 */

#endif
