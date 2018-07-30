#include "sym_table.h"

#include "basic_interface.h"

#define TEST_SIZE 10

int main()
{
  sym_table st = Sym_table();
  
  //test add/remove symbol
  init_basic_interfaces();
  
  int i = 3;
  add_symbol(st, "key", TYPE_ENUM_INT, &i);
  add_symbol(st, "key1", TYPE_ENUM_INT, &i);
  add_symbol(st, "key2", TYPE_ENUM_INT, &i);
  add_symbol(st, "key3", TYPE_ENUM_INT, &i);

  add_scope(st);
  /*
  add_symbol(st, "key", TYPE_ENUM_INT, &i);
  add_symbol(st, "key1", TYPE_ENUM_INT, &i);
  add_symbol(st, "key2", TYPE_ENUM_INT, &i);
  add_symbol(st, "key3", TYPE_ENUM_INT, &i);
  */
  
  for(int i = 0; i < TEST_SIZE; i++) {
    add_scope(st);
    for(int i = 0; i < TEST_SIZE; i++) {

      string tmp = basic_interface_int.toString(&i);
      add_symbol(st,
		 tmp,
		 TYPE_ENUM_INT, &i);
      free(tmp);
    
    }
    print_scope((st->data)[st->size - 1]);
  }

  pair p = find_symbol(st,"key2");
  pair p2 = find_symbol(st,"4");


  string tmp1 = sym_dataToString((sym_data)(p->value));
  string tmp2 = sym_dataToString((sym_data)(p2->value));
  printf("%s\n", tmp1);
  printf("%s\n", tmp2);

  free(tmp1);
  free(tmp2);
  
  free_sym_table(st);
}
