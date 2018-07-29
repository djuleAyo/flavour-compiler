#include "interpreter.h"

basic_type_value interpret_expr(ast_node n, sym_table st)
{
  switch(n->type) {
  case AST_NODE_TYPE_CON:
    return n->node.con;
    break;
  case AST_NODE_TYPE_ID:
    {
      pair p = find_symbol(st, n->node.id->key);
      type_enum t =  ((sym_data)(p->value))->type_value->type;
      if( t == TYPE_ENUM_INT) 
	return Basic_type_value( t,
				 &(((sym_data)(p->value))->
				   type_value->var.num));
      else
	return Basic_type_value( t, (((sym_data)(p->value))->
				     type_value->var.str));
    }
    break;
  case AST_NODE_TYPE_OP:
    {
      basic_type_value op1 = interpret_expr((n->node.op->opers)[0], st);
      basic_type_value op2 = n->node.op->oper_num == BINARAN ?
	interpret_expr((n->node.op->opers)[1],st) : NULL;

      int a = 0;
      
      basic_type_value ret_val = Basic_type_value(TYPE_ENUM_INT, &a);
      switch(n->node.op->oper_type)
	{
	case '+':
	  ret_val->var.num = op1->var.num + op2->var.num;
	  break;
	case '-':
	  ret_val->var.num = op1->var.num - op2->var.num;
	  break;
	case '*':
	  ret_val->var.num = op1->var.num * op2->var.num;
	  break;
	case '/':
	  ret_val->var.num = op1->var.num / op2->var.num;
	  break;
	default:
	  assert(0);
	}
      free(op1);
      if(op2)
	free(op2);
      return ret_val;
    }
    break;
  default:
    assert(0);
  }
}
