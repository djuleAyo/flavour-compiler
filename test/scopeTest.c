#include "scope.h"


#include "basic.h"
#include "lambda.h"

int main() {

  init_basic_types();
  init_scope();

  basic_object o1 = make_int_object(5);
  basic_object o2 = make_string_object("hello objects");


  type l1_type = make_type_function_node(int_type, int_type);
  type l2_type = make_type_function_node(int_type, string_type);
  lambda l1 = make_lambda(l1_type, NULL, global_scope);
  lambda l2 = make_lambda(l2_type, NULL, global_scope);

  scope_add(global_scope, "hello overloads1", l1);
  scope_add(global_scope, "hello overloads1", l2); /*  */


  scope_add(global_scope, "test", o1);
  scope_add(global_scope, "test1", o2);

  basic_object o3 = make_string_object("assign");
  scope_assign(global_scope, "test1", o3);
  string asd = object_to_string(scope_find(global_scope, "test1", NULL));
  printf("assign %s\n", asd);
  free(asd);
  free_object(o3);

  object found = scope_find(global_scope, "hello overloads1", l2_type);

  string tmp3 = type_to_string(found->type_val);
  printf("found %s\n",tmp3);

  free(tmp3);

  /* free_object(o1); */
  /* free_object(o2); */

  // free_type(l1_type);
   // free_type(l2_type);

  deinit_scope();
  deinit_basic_types();
}
