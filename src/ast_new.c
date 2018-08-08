#include "ast_new.h"

ast_node make_ast()
{
  ast_node new = malloc(sizeof(struct _ast_node));
  assert(new);

  return new;
}

ast_node ast_int_con(int x)
{
  ast_node new = make_ast();
  new->node_type = AST_NODE_INT_CON;
  new->data.int_con = x;
  return new;
}
ast_node ast_string_con(string s)
{
  ast_node new = make_ast();
  new->node_type = AST_NODE_STRING_CON;
  new->data.string_con = s;
  return new;
}

ast_node ast_bin_node(ast_node left, ast_node right, ast_node_type t)
{
  ast_node new = make_ast();
  new->node_type = t;
  new->data.nodes = malloc(sizeof(ast_node) * 2);
  assert(new->data.nodes);

  (new->data.nodes)[0] = left;
  (new->data.nodes)[1] = right;

  return new;
}

ast_node ast_un_node(ast_node left, ast_node_type t)
{
  ast_node new = make_ast();
  new->node_type = t;
  new->data.nodes = malloc(sizeof(ast_node));
  assert(new->data.nodes);

  (new->data.nodes)[0] = left;
  return new;
}


ast_node ast_print(ast_node n)
{
  ast_node new = make_ast();

  new->node_type = AST_NODE_PRINT;
  new->data.nodes = malloc(sizeof(ast_node));
  assert(new->data.nodes);

  (new->data.nodes)[0] = n;

  return new;
}

ast_node make_ast_block()
{
  ast_node new = make_ast();
  new->node_type = AST_NODE_BLOCK;

  new->data.block = malloc(sizeof(struct _ast_block));
  assert(new->data.block);
  new->data.block->size = 0;
  new->data.block->volume = INITIAL_BLOCK_VOLUME;
  new->data.block->nodes = malloc(sizeof(struct _ast_node) * INITIAL_BLOCK_VOLUME);
  assert(new->data.block->nodes);

  return new;
}

void add_to_block(ast_node b, ast_node stmt)
{
  assert(b->node_type == AST_NODE_BLOCK);

  if(b->data.block->size == b->data.block->volume)
    {
      b->data.block->volume *= 2;
      b->data.block->nodes = realloc( b->data.block->nodes,b->data.block->volume * sizeof(struct _ast_node));
    }
  (b->data.block->nodes)[b->data.block->size++] = stmt;
}


ast_node ast_id(string id)
{
  ast_node new = make_ast();
  new->node_type = AST_NODE_ID;
  new->data.string_con = id;

  return new;
}

ast_node ast_while(ast_node condition, ast_node body)
{
  ast_node new = make_ast();
  new->node_type = AST_NODE_WHILE;
  new->data.nodes = malloc(sizeof(ast_node) * 2);
  assert(new->data.nodes);

  (new->data.nodes)[0] = condition;
  (new->data.nodes)[1] = body;

  return new;
}
