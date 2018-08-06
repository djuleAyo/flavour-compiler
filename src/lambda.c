#include "lambda.h"
#include "errors.h"
#include "flavour.h"


lambda make_lambda(type t, ast_node ast, scope lambda_parrent)
{
  if(t->node_type != TYPE_FUNCTION_NODE)
    assert(!E_LAMBDA_NOT_LAMBDA);
  assert(lambda_parrent && "cant make lambda without lambda parrent");

  lambda new = malloc(sizeof(struct _object));
  assert (new);

  lambda_value new_val = malloc(sizeof(struct _lambda_value));
  assert(new_val);

  new_val->ast = ast;
  new_val->lambda_parrent = lambda_parrent;
  lambda_parrent->ref_count++;

  new->type_val = t;
  new->data = new_val;

  return new;
}

//does not free shared resources - ast
void free_lambda(lambda l)
{
  if(!l) return;

  scope s = ((lambda_value)(l->data))->lambda_parrent;

  s->ref_count--;

  if((s->ref_count == 0) && (s != current_scope))
    {
      free_scope_branch(s);
    }

  free(l->data);
  free_type(l->type_val);
  free(l);
}


lambda clone_lambda(lambda l)
{
  return make_lambda(clone_lambda_type(l->type_val),
                     ((lambda_value)(l->data))->ast,
                     ((lambda_value)(l->data))->lambda_parrent);
}


//updates ast
lambda lambda_define(lambda l, ast_node ast)
{
  if(((lambda_value)(l->data))->ast)
    assert(0 && "function already defined\n");

  ((lambda_value)(l->data))->ast = ast;

  return l;
}

//a lambda can return ANY object type - this is runtime function - must be
//ported to executable. Takes list of objects
object lambda_execute(lambda l, list args, scope current_scope)
{
  UNUSED(l);
  UNUSED(args);
  UNUSED(current_scope);
  //makes new scope as a leaf of execution branch - stack
  //
  return NULL;
  }
