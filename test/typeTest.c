#include "type.h"
#include "list.h"

int main() {
  /*
  type c = make_type_composite_node("struct B", "prop1");

  type i1 = make_type_basic_node(BASIC_TYPE_INT, "a");
  type i2 = make_type_basic_node(BASIC_TYPE_INT, "b");

  type A = make_type_composite_node("struct A", NULL);

  type i3 = make_type_basic_node(BASIC_TYPE_STRING, "b");



  for(int i = 0; i < 1000; i++) {
    add_node_to_composite(c->node.composite_node,
                          make_type_basic_node(BASIC_TYPE_STRING, )
                          );
  }


  add_node_to_composite(c->node.composite_node, i1);
  add_node_to_composite(c->node.composite_node, i2);

  add_node_to_composite(A->node.composite_node, c);
  add_node_to_composite(A->node.composite_node, i3);


  string asd = type_to_string(get_ith_leaf(A, 1));
  printf("trece dete %s\n", asd);
  free(asd);


  printf("offset od prop1 je %d\n", operator_dot(A, "prop1"));
  printf("offset od b je %d\n", operator_dot(A, "b"));

  printf("offset od a u struct B je %d\n", operator_dot(c, "a"));
  printf("offset od b u struct B je %d\n", operator_dot(c, "b"));



  string tmp = type_to_string(A);
  printf("%s\n", tmp);
  free(tmp);

  free_type(A);
  */
  //====================================================================


  //struct
  type t1 = make_type_basic_node(BASIC_TYPE_INT, "a");
  /* type t2 = make_type_basic_node(BASIC_TYPE_INT, "b"); */
  /* type t3 = make_type_basic_node(BASIC_TYPE_INT, NULL); */
  /* type t4 = make_type_basic_node(BASIC_TYPE_STRING, NULL); */

  type arg_list = make_type_composite_node("struct B", "prop1");
  add_node_to_composite(arg_list->node.composite_node, t1);
  add_node_to_composite(arg_list->node.composite_node, t1);


  type arg_list2 = make_type_composite_node("struct G", NULL);
  add_node_to_composite(arg_list2->node.composite_node, t1);
  add_node_to_composite(arg_list2->node.composite_node,t1);
  
  type f1 = make_type_function_node(arg_list, t1);
  type f2 = make_type_function_node(arg_list2, t1);


  type f3 = make_type_function_node(f1,t1);

  printf("equals: %s\n", type_equals(f2,f1)?"yes":"no");
  free_type(f3);
  string tmp = type_to_string(f2);
  free_type(arg_list2);
  printf("%s\n", tmp);
  free(tmp);

  free_type(t1);
  /* free_type(t2); */
  /* free_type(t3); */
  /* free_type(t4); */
  free_type(f1);
  free_type(f2);
  free_type(arg_list);
  return 0;
}

