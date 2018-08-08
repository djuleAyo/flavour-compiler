#include "struct.h"
#include "list.h"

int main()
{
  init_basic_types();



  type l1_type = make_type_composite_node("strukturica mujadin",NULL);

  add_node_to_composite(l1_type->node.composite_node, make_type_basic_node(BASIC_TYPE_INT, "ime1"), "ime1");
  add_node_to_composite(l1_type->node.composite_node, make_type_basic_node(BASIC_TYPE_INT,"asd"), "ime2");

  list l = make_list();

  int broj = 7;
  int broj2 = 1;
  list_add_end(&l,&broj);
  string str = strdup("string batice");
  list_add_end(&l, &broj2);
  object strukturica = make_struct(l1_type, l);

  printf("polje strukture %d %d\n", *(int*)(strukturica->data), *(int*) (((char*)(strukturica->data)) + sizeof(int)));

  free_list(&l);
  free(str);
  //free_object(strukturica);
  free_type(l1_type);
  deinit_basic_types();
}
