#ifndef _ast_new_H
#define _ast_new_H

#include "flavour.h"

typedef enum {
  AST_NODE_INT_CON,
  AST_NODE_STRING_CON,

  AST_NODE_ID,

  //operators
  AST_NODE_OP_PLUS,
  AST_NODE_OP_MINUS,
  AST_NODE_OP_MUL,
  AST_NODE_OP_DIV,
  AST_NODE_OP_LT,
  AST_NODE_OP_GT,
  AST_NODE_OP_LE,
  AST_NODE_OP_GE,
  AST_NODE_OP_EQ,
  AST_NODE_OP_NE,
  AST_NODE_OP_UN_MIN,
  AST_NODE_OP_DOT,

  AST_NODE_WHILE,
  AST_NODE_IF,
  AST_NODE_FOR,


  AST_NODE_DEF,
  AST_NODE_BLOCK,
} ast_node_type;

struct _ast_node {
  union {
    int int_con;
    string string_con;
    struct _ast_node** nodes;
  } data;
  ast_node_type node_type;
};

typedef struct _ast_node* ast_node;
typedef ast_node ast;

ast_node make_ast();

ast_node ast_int_con(int x);
ast_node ast_string_con(string s);

#endif
