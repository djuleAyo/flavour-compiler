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


void interpret_stmt(ast_node n, sym_table st)
{
    switch(n->type)
    {
        case AST_NODE_TYPE_OP:
        {
            switch(n->node.op->oper_type)
            {
                case '=':
                {
                    basic_type_value b = interpret_expr((n->node.op->opers)[1], st);
                    
                    add_symbol(st, (n->node.op->opers)[0]->node.id->key, b->type, (b->type == TYPE_ENUM_INT) ? (void*)&(b->var.num) : (void*)b->var.str);
                    
                    break;
                }
                case 'p':
                {
                    basic_type_value b = interpret_expr((n->node.op->opers)[0], st);
                    if(b->type == TYPE_ENUM_INT)
                        printf("%d\n",b->var.num);
                    else
                        printf("%s\n",b->var.str);
                    
                    break;
                }
                default:
                    assert(0);
            }
            break;
        }
        case AST_NODE_TYPE_BLOCK:
        {
            {
                add_scope(st);
                unsigned i;
                for(i = 0; i < n->node.block->size; i++)
                    interpret_stmt((n->node.block->stmts)[i], st);
                end_scope(st);
            break;
            }
        }
        default:
            assert(0);
        
    }
    
}























