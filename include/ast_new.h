#ifndef _ast_new_H
#define _ast_new_H

#define INITIAL_BLOCK_VOLUME 10
#include "flavour.h"
#include "type.h"

typedef enum {
  //littera;
  AST_NODE_INT_CON,
  AST_NODE_STRING_CON,

  AST_NODE_DCL,

  //object
  AST_NODE_LAMBDA,
  AST_NODE_TYPE,
  AST_NODE_STRUCT,
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
  AST_NODE_OP_UN_MINUS,
  
  //statements
  AST_NODE_WHILE,
  AST_NODE_IF,
  AST_NODE_ASSIG,
  AST_NODE_FOR,
  AST_NODE_DEF,
  AST_NODE_BLOCK,
  AST_NODE_PRINT
} ast_node_type;

struct _ast_node;

struct _ast_block
{
  int size;
  int volume;
  struct _ast_node** nodes;
};
typedef struct _ast_block* ast_block;


struct _ast_node {
  union {
    int int_con;
    string string_con;
    ast_block block;
    type type_val;
    struct _ast_node** nodes;
  } data;
  ast_node_type node_type;
};

typedef struct _ast_node* ast_node;
typedef ast_node ast;

ast_node make_ast();

ast_node ast_print(ast_node n);
ast_node make_ast_block();
void add_to_block(ast_node block, ast_node stmt);

ast_node ast_int_con(int x);
ast_node ast_string_con(string s);
ast_node ast_id(string id);

ast_node ast_bin_node(ast_node left, ast_node right, ast_node_type t);
ast_node ast_un_node(ast_node left, ast_node_type t);

ast_node ast_while(ast_node condition, ast_node body);


#endif
