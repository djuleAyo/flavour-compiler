#include "pair.h"
#include "flavour.h"
#include "errors.h"
#include <string.h>

pair make_pair(string k, void* v)
{

  pair new = malloc(sizeof(struct _pair));
  assert(new);

  new->key = strdup(k);
  new->data = v;

  return new;
}

void free_pair(pair p)
{
  free(p->key);
  free(p);
}

bool pair_has_key(pair p, string k)
{
    if(!p || !k)
        assert(!E_PAIR_HAS_KEY_INVAL);
    return strcmp(p->key,k)?false:true;
}
