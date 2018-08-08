#include "interpreter.h"
#include "flavour.h"
#include "object.h"


ast_node interpret_expr(ast_node n)
{
#define left (interpret_expr((n->data.nodes)[0])->data.int_con)
#define right (interpret_expr((n->data.nodes)[1])->data.int_con)
  ast_node ret_val = make_ast();

  ret_val->node_type = AST_NODE_INT_CON;

  int val;
  switch(n->node_type) {
  case AST_NODE_INT_CON:
    return n;
    break;
  case AST_NODE_OP_PLUS:
    val = left + right;
    break;
  case AST_NODE_OP_MINUS:
    val = left - right;
    break;
  case AST_NODE_OP_MUL:
    val = left * right;
    break;

  case AST_NODE_OP_DIV:
    val = left / right;
    break;

  case AST_NODE_OP_LT:
    val = left < right;
    break;

  case AST_NODE_OP_GT:
    val = left > right;
    break;

  case AST_NODE_OP_LE:
    val = left <= right;
    break;

  case AST_NODE_OP_GE:
    val = left >= right;
    break;

  case AST_NODE_OP_EQ:
    val = left == right;
    break;

  case AST_NODE_OP_NE:
    val = left != right;
    break;
  case AST_NODE_OP_UN_MINUS:
    val = -left;
    break;

  case AST_NODE_ID:
    {
      //terba da se prepakuje - samo za intove sada
      object o = scope_find(current_scope, n->data.string_con, NULL, true);
      assert(o && "Using undefined variable");
      return ast_int_con(*(int*)(o->data));
      break;
    }
  }

  ret_val->data.int_con = val;
  return ret_val;
#undef left
#undef right
}
void interpret_stmt(ast_node n)
{
  switch(n->node_type) {
  case AST_NODE_PRINT:
    printf("%d\n", interpret_expr((n->data.nodes)[0])->data.int_con);
    break;
  case AST_NODE_BLOCK:
    current_scope = make_scope(current_scope, NULL);

    for(int i = 0; i < n->data.block->size; i++) {
      interpret_stmt((n->data.block->nodes)[i]);
    }
    scope tmp = current_scope->scope_parrent;
    free_scope(current_scope);
    current_scope = tmp;

    break;
  case AST_NODE_WHILE: {
    current_scope = make_scope(current_scope, NULL);

    int condition;
    while(condition = interpret_expr((n->data.nodes)[0])->data.int_con) {
      interpret_stmt((n->data.nodes)[1]);
    }

    scope tmp = current_scope->scope_parrent;
    free_scope(current_scope);
    current_scope = tmp;


    break;
    }
  case AST_NODE_ASSIG: {
    scope_assign((n->data.nodes)[0]->data.string_con,
                 make_int_object(interpret_expr((n->data.nodes)[1])->data.int_con)
                 );

    break;

  }
  case AST_NODE_DEF: {
    scope_add(current_scope, (n->data.nodes)[0]->data.string_con,
              make_int_object((n->data.nodes)[1]->data.int_con)
              );
      }
  }
}
