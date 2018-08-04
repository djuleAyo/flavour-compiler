#include "lambda.h"
#include "errors.h"
#include "flavour.h"


lambda make_lambda(type t, ast_node ast, stack parrenting_scope)
{
  if(t->node_type != TYPE_FUNCTION_NODE)
    assert(!E_LAMBDA_NOT_LAMBDA);
  lambda new = malloc(sizeof(struct _object));
  assert (new);

  lambda_value new_val = malloc(sizeof(struct _lambda_value));
  assert(new_val);

  new_val->ast = ast;
  mew_val->next = NULL;



  if(t->node.function_node->return_type->node_type == TYPE_FUNCTION_NODE)
    {
      new_val->parenting_scopes = parrenting_scope;
    }
  else
    {
      new_val->pareting_scope = NULL;
    }

  new->type = t;
  new->value = new_val;

  return new;

}
void free_lambda(lambda lambda_list)
{
  if(!lambda_list) return;

  //dont free shared resources - ast and non 1st pareting_scope
  stack parrenting_scopes = ((lambda_value)(lamdba_list->value))->parenting_scopes;
  if(parrenting_scopes->size)
    {
      free_scope(stack_pop(parrenting_scopes));
    }
  free_lambda(((lambda_value)(lamdba_list->value))->next);
}

//returns same lamda as sent in for chaining
lambda lambda_add_overload(lambda* lambda_list, type t, ast_node ast, stack parentning_scope)
{
  if(!(*lambda_list))
    {
      *lambda_list = make_lambda(t,ast,parentning_scope );
      return *lambda_list;
    }
  if(type_equals(t, (*lambda_list)->type))
    assert(!E_LAMBDA_MULTY_DEF);

  lambda tmp =*lamdba_list;
  lambda next_tmp = ((lambda_value)(tmp->value))->next;


  while(next_tmp)
    {
      if(type_equals( next_tmp->type, t))
        assert(!E_LAMBDA_MULTY_DEF);
      tmp = next_tmp;
      next_tmp = ((lambda_value)(next_tmp->value))->next;
    }
  (((lambda_value)(tmp->value))->next = make_lambda(t, ast, parentning_scope);
  return ((lambda_value)(tmp->value))->next;
}

lambda lambda_find_overload(lambda lambda_list, type t)
{
  if(!lambda_list)
    return NULL;
  if(type_equals(lambda_list->type, t))
    return lambda_list;
  return lambda_find_overload( ((lambda_value)(lambda_list))->next, t);
}

//updates ast
lambda lambda_update(lambda lambda_list, type t, ast_node ast)
{
  lambda update = lambda_find_overload(lambda_list, t);
  if(!update)
    assert(!E_LAMBDA_NOENT);
  ((lambda_value)(update->value))->ast = ast;
  ((lambda_value)(update->value))->type = t;

  return update;
}
//a lambda can return ANY object type - this is runtime function - must be
//ported to executable. Takes list of objects
object lambda_execute(lambda lambda_list,  list args)
{

}
