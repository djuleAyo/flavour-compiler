#include "flavour.h"
#include "ast.h"
#include "basic_interface.h"
#include "sym_table.h"

/* node_con Const_node(type_enum t, var_union v) */
/* { */
/*     node_con new = malloc(sizeof(struct _ast_node_con)); */
/*     assert(new); */
    
/*     new->type = t; */
/*     new->var = v; */
/*     return new; */
/* } */

//KLJUCEVE NE KOPIRAM U DRVO
node_id Id_node(string key)
{
    node_id new = malloc(sizeof(struct _ast_node_id));
    assert(new);
    new->key = key;
    return new;
}

node_op Un_oper_node(char oper_type, ast_node operand)
{
    node_op new = malloc(sizeof(struct _ast_node_op));
    assert(new);
    new->oper_num = UNARAN;
    new->oper_type = oper_type;
    new->opers = malloc(sizeof(struct _ast_node) * UNARAN);
    assert(new->opers);
    (new->opers)[0] = operand;
    return new;
}

node_op Bin_oper_node(char oper_type, ast_node operand1, ast_node operand2)
{
    node_op new = malloc(sizeof(struct _ast_node_op));
    assert(new);
    new->oper_num = BINARAN;
    new->oper_type = oper_type;
    new->opers = malloc(sizeof(struct _ast_node) * BINARAN);
    assert(new->opers);
    (new->opers)[0] = operand1;
    (new->opers)[1] = operand2;
    return new;
}

node_block Block_node()
{
    node_block new = malloc(sizeof(struct _ast_node_block));
    assert(new);
    new->size = 0;
    new->volume = BLOCK_INITIAL_VOLUME;
    new->stmts = malloc(sizeof(ast_node) * BLOCK_INITIAL_VOLUME);
    assert(new->stmts);
    return new;
}


ast_node Ast_node(ast_node_type t)
{
    ast_node new = malloc(sizeof(struct _ast_node));
    assert(new);
    new->type = t;
    return new;
}

ast_node Ast_node_con(type_enum t, void *v)
{
    ast_node new = Ast_node(AST_NODE_TYPE_CON);

    new->node.con = Basic_type_value(t, v);

    return new;
}

ast_node Ast_node_id(string key)
{
    ast_node new = Ast_node(AST_NODE_TYPE_ID);
    new->node.id = Id_node(key);
    return new;
}

ast_node Ast_node_un_oper(char oper_type, ast_node operand)
{
    ast_node new = Ast_node(AST_NODE_TYPE_OP);
    new->node.op = Un_oper_node(oper_type, operand);
    return new;
}

ast_node Ast_node_bin_oper(char oper_type, ast_node operand1, ast_node operand2)
{
    ast_node new = Ast_node(AST_NODE_TYPE_OP);
    new->node.op = Bin_oper_node(oper_type, operand1, operand2);
    return new;
}

ast_node Ast_node_block()
{
    ast_node new = Ast_node(AST_NODE_TYPE_BLOCK);
    new->node.block = Block_node();
    return new;
}



void add_stmt_to_block(node_block block, ast_node stmt)
{   
    if(block->size + 1 == block->volume)
    {
      block->volume *= 2;
      block->stmts = realloc(block->stmts, block->volume);
      assert(block->stmts);
    }
    (block->stmts)[block->size++] = stmt;
}

string node_conToString(node_con n)
{
  switch(n->type) {
  case TYPE_ENUM_INT:
    return basic_interface_int.toString(&(n->var.num));
    break;
  case TYPE_ENUM_STRING:
    return basic_interface_string.toString(n->var.str);
    break;
  default:
    assert(0);
  }
}

void print_ast_node(ast_node n)
{
  string tmp;
  switch(n->type) {
  case AST_NODE_TYPE_CON:
    tmp = node_conToString(n->node.con);
    printf("%s", tmp);
    break;

  case AST_NODE_TYPE_OP:
    {
      switch(n->node.op->oper_num)
	{
	case UNARAN:
	  printf("%c ", n->node.op->oper_type);
	  print_ast_node((n->node.op->opers)[0]);
	  break;
	case BINARAN:
	  print_ast_node((n->node.op->opers)[0]);
	  printf(" %c ", n->node.op->oper_type);
	  print_ast_node((n->node.op->opers)[1]);
	  break;
	default:
	  assert(0);
	}
    }
    break;
  case AST_NODE_TYPE_BLOCK:
    /*
    tmp = node_blockToString(n->node.block);
    printf("block{\n%s\n}\n",tmp);
    */
    break;

  case AST_NODE_TYPE_ID:
    printf("id: %s\n", n->node.id->key);
    break;
  default:
    assert(0);
  }
  free(tmp);
}






