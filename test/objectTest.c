#include "object.h"
#include "type.h"
#include "list.h"



int main()
{
  //TESTED OLD OBJECT IMPLEMENTATION WITHOUT FAIL
  //when no lambdas were present

  /* type i1 = make_type_basic_node(BASIC_TYPE_INT, "a"); */
  /* type i2 = make_type_basic_node(BASIC_TYPE_INT, "b"); */
  /* type c = make_type_composite_node("struct B", "prop1"); */
  /* type i3 = make_type_basic_node(BASIC_TYPE_STRING, "b"); */
  /* type A = make_type_composite_node("struct A", NULL); */


  /* add_node_to_composite(c->node.composite_node, i1); */
  /* add_node_to_composite(c->node.composite_node, i2); */

  /* add_node_to_composite(A->node.composite_node, c); */
  /* add_node_to_composite(A->node.composite_node, i3); */


  /* int a = 5; */
  /* int b =2; */
  /* string str = strdup("test"); */

  /* type type_int = make_type_basic_node(BASIC_TYPE_INT, NULL); */
  /* type type_string = make_type_basic_node(BASIC_TYPE_STRING, NULL); */

  /* list l1 = make_list(); */
  /* list l2 = make_list(); */
  /* list l3 = make_list(); */
  /* list lc = make_list(); */

  /* list_add_end(&l1, &a); */
  /* list_add_end(&l2, &b); */
  /* list_add_end(&l3, str); */

  /* object o1 = make_object(type_int, l1); */
  /* object o2 = make_object(type_int, l2); */
  /* object o3 = make_object(type_string, l3); */

  /* list_add_end(&lc, o1); */
  /* list_add_end(&lc, o2); */
  /* list_add_end(&lc, o3); */


  /* object o4 = make_object(A, lc); */

  /* free_list(&l1); */
  /* free_list(&l2); */
  /* free_list(&l3); */
  /* free_list(&lc); */

  /* free_type(A); */
  /* free_type(type_int); */
  /* free_type(type_string); */

  /* free_object(o1); */
  /* free_object(o2); */
  /* free_object(o3); */
  /* free_object(o4); */

}
