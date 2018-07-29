#include "sym_table.h"
 
sym_table Sym_table()
{
  hash globalScope = Hash();
  
  sym_table st = Stack();
  push(st, globalScope);

  return st;
}

void free_sym_table(sym_table st)
{
int i = st->size - 1;

  while(i >= 0) {
    end_scope(st);
    i--;
  }
  free_stack(st);
}
hash add_scope(sym_table st)
{
  hash h = Hash();
  push(st, h);

  return h;
}

void end_scope(sym_table st)
{
  hash ending_scope = pop(st);

  //hash doesn't know how to free content it hold
  //sym table hold types so here we can clear a hash
  for(unsigned i = 0; i < ending_scope->volume; i++) {
    //remove bucket lists
    if(!(ending_scope->data)[i]) continue;

    bucket b = (ending_scope->data)[i];
    bucket tmp;
    while(b) {
      tmp = b->next;

      free_sym_data((sym_data)(b->content->value));

      free_bucket(b);
      
      b = tmp;
    }
  }
  
  free_hash(ending_scope);
}

//every bucket list is printed in 1 line
void print_scope(hash h)
{
  printf("SCOPE---------------------------\n");
  for(unsigned i = 0; i < h->volume; i++) {
    if(!(h->data)[i]) continue;

    bucket tmp = (h->data)[i];
    while(tmp) {

      string sym_data_str = sym_dataToString(tmp->content->value);
      printf("(\"%s\": %s)\t", tmp->content->key, sym_data_str);

      free(sym_data_str);
	  
      tmp = tmp->next;
    }
    printf("\n");

  }
}

void add_symbol(sym_table st, string key, type_enum t, void* var)
{
  hash_add(top(st), key, Sym_data(t, var));
}
pair find_symbol(sym_table st, string key)
{
  int current_scope = st->size - 1;
  while(current_scope >= 0) {
    pair var = hash_find((st->data)[current_scope], key);

    if(var) return var;
    
    current_scope--;
  }
  assert(0);
}
