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
