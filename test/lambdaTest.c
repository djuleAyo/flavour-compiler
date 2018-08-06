#include "lambda.h"
#include "scope.h"


int main()
{
    type t1 = make_type_basic_node(BASIC_TYPE_INT, "a");
  /* type t2 = make_type_basic_node(BASIC_TYPE_INT, "b"); */
  /* type t3 = make_type_basic_node(BASIC_TYPE_INT, NULL); */
  /* type t4 = make_type_basic_node(BASIC_TYPE_STRING, NULL); */

  //{int, int}
  type arg_list = make_type_composite_node("struct B", "prop1");
  add_node_to_composite(arg_list->node.composite_node, t1);
  add_node_to_composite(arg_list->node.composite_node, t1);

  //another {int, int}
  type arg_list2 = make_type_composite_node("struct G", NULL);
  add_node_to_composite(arg_list2->node.composite_node, t1);
  add_node_to_composite(arg_list2->node.composite_node,t1);

  //{int, int} (int)
  type f1 = make_type_function_node(arg_list, t1);
  //{int, int} (int)
  type f2 = make_type_function_node(arg_list2, t1);

  //{int, int}(int)(int)
  type f3 = make_type_function_node(f1,t1);

  init_scope();


  lambda l  = make_lambda(f3, NULL, current_scope);

  free_lambda(l);

  deinit_scope();

  free_type(t1);
  free_type(f1);
  free_type(f2);
  //free_type(f3);
  free_type(arg_list);
  free_type(arg_list2);
}
