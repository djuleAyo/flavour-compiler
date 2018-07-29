#include "pair.h"
#include "flavour.h"
#include "basic_interface.h"

pair Pair(string key, void* value)
{
  pair new = malloc(sizeof(struct _pair));
  assert(new);

  new->key = strdup(key);
  new->value = value;

  return new;
}

void free_pair(pair p)
{
  free(p->key);
  free(p);
}

//REPLACE this implementation where it is needed
/*
#define OTHER_CHARS 10
//to string function allocate memory and user needs to free it
string pair_to_string(pair p)
{
  string val_str = value_to_string(p->value);
  string ret_str = malloc(strlen(p->key)
			  + OTHER_CHARS
			  + strlen(val_str));

  sprintf(ret_str, "(\"%s\", %s)", p->key, val_str);

  free(val_str);
  
  return NULL;
}
#undef OTHER_CHARS

*/