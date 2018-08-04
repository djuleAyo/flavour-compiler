#ifndef _LAMBDA_H
#define _LAMBDA_H

#include "stack.h"
#include "scope.h"

#include "ast.h"
#include "object.h"


//definition: lambda is object(type, value union) that contain a function
#define object lambda;

struct _lambda_value {
  //shared resource - ptr to subtree of whole programm
  ast_node ast;
  //may remove only 1st instance of parent since others are shared
  stack parenting_scopes;
  //must be lambda
  /* not using implemented list because it requires definition
     of new type that is not exposed to in flavour language - overload type */
  lambda next;
};
typedef struct _lambda_value* lambda_value;


/*
  Parents are saved execution scopes that created a lamdba, which needs access
  to those scopes(parent scope). Those scopes are stored in resulting lambda
 */


// make_lambda(t, NULL, stack_scope); ==> function declaration
// make_lambda(t, ast, stack_scope); ==> function definition with declaration
// make_lambda(t, ast, NULL); ==> return type is not lambda || returning lambda but defined in global scope
lambda make_lambda(type t, ast_node ast, stack parrenting_scope);
void free_lambda(lambda lambda_list);

//returns same lamda as sent in for chaining
lambda lambda_add_overload(lambda* lambda_list, type t, ast_node ast, stack parrenting_scope);
lambda lambda_find_overload(lambda lambda_list, type t);

//for definition of previously declared lambda
lambda lambda_update(lambda lambda_list, type t, ast_node ast);
//a lambda can return ANY object type - this is runtime function - must be
//ported to executable. Takes list of objects
object lambda_execute(lambda lambda_list,  list args);


#endif
