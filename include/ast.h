#pragma once

#include "type.h"

/* struct _ast_node {}; */
/* typedef struct _ast_node* ast_node; */

/* #define BLOCK_INITIAL_VOLUME 10 */
/* #define UNARAN 1 */
/* #define BINARAN 2 */

/* typedef enum { */
/*   AST_NODE_TYPE_CON, */
/*   AST_NODE_TYPE_ID, */
/*   AST_NODE_TYPE_OP, */
/*   AST_NODE_TYPE_BLOCK */
/* } ast_node_type; */

/* struct _basic_type_value con; */
/* struct _ast_node_id id; */
/* struct _ast_node_op op; */
/* struct _ast_node_block block; */

/* typedef union { */
/*   basic_type_value con; */
/*   struct _ast_node_id* id; */
/*   struct _ast_node_op* op; */
/*   struct _ast_node_block* block; */
/* } ast_node_union; */

/* //"super class" of all nodes */
/* struct _ast_node { */
/*   ast_node_type type; */
/*   ast_node_union node; */
/* }; */
/* typedef struct _ast_node* ast_node; */

/* typedef basic_type_value node_con; */

/* struct _ast_node_id */
/* { */
/*     string key; */
/* }; */
/* typedef struct _ast_node_id* node_id; */

/* struct _ast_node_op */
/* { */
/*     unsigned oper_num; */
/*     char oper_type; */
/*     ast_node *opers; */
/* }; */
/* typedef struct _ast_node_op* node_op; */

/* struct _ast_node_block */
/* { */
/*     unsigned size; */
/*     unsigned volume; */
/*     ast_node *stmts; */
/* }; */
/* typedef struct _ast_node_block* node_block; */

/* ast_node ast_node_con(type_enum t, void *v); */
/* ast_node ast_node_id(string key); */
/* ast_node ast_node_un_oper(char oper_type, ast_node operand); */
/* ast_node ast_node_bin_oper(char oper_type, ast_node operand1, ast_node operand2); */
/* ast_node ast_node_block(); */


/* void add_stmt(node_block block, ast_node stmt); */

/* string node_conToString(node_con n); */
/* void print_ast_node(ast_node n); */
