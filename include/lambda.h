#ifndef _LAMBDA_H
#define _LAMBDA_H

#include "scope.h"
#include "ast.h"
#include "object.h"

struct _scope;
typedef struct _scope* scope;


//definition: lambda is object(type, value union) that contain a function
typedef object lambda;

struct _lambda_value {
  //shared resource - ptr to subtree of whole programm
  ast_node ast;
  scope lambda_parrent;
};
typedef struct _lambda_value* lambda_value;



//==============================================================================

// make_lambda(t, NULL, stack_scope); ==> function declaration
// make_lambda(t, ast, stack_scope); ==> function definition with declaration
lambda make_lambda(type t, ast_node ast, scope lambda_parrent);
void free_lambda(lambda l);

lambda clone_lambda(lambda l);

//for definition of previously declared lambda
lambda lambda_define(lambda l, ast_node ast);

//a lambda can return ANY object type - this is runtime function - must be
//ported to executable. Takes list of objects
object lambda_execute(lambda l, list args, scope current_scope);


#endif
