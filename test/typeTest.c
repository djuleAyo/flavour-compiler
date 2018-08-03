#include "type.h"
#include "list.h"

int main() {
  type c = make_type_composite_node("struct B", "prop1");

  type i1 = make_type_basic_node(BASIC_TYPE_INT, "a");
  type i2 = make_type_basic_node(BASIC_TYPE_INT, "b");

  type A = make_type_composite_node("struct A", NULL);

  type i3 = make_type_basic_node(BASIC_TYPE_STRING, "b");


  /*
  for(int i = 0; i < 1000; i++) {
    add_node_to_composite(c->node.composite_node,
                          make_type_basic_node(BASIC_TYPE_STRING, )
                          );
  }
  */

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
}