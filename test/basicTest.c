#include "basic.h"

int main() {
  init_basic_types();

  basic_object o1 = make_int_object(5);
  basic_object o2 = make_string_object("hello objects");


  printf("%d\n", *(int*)(o1->data));
  printf("%s\n", (string)(o2->data));

  free_int_object(o1);
  free_string_object(o2);

  deinit_basic_types();
}
