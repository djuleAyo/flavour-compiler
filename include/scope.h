#ifndef _SCOPE_H
#define _SCOPE_H

#include "hash.h"

/* Module description - scope is hash of names(strings)
   into object.
*/

typedef hash scope;

object scope_add(string key, object o) {
  hash_add(key, o);
}

//scope knows its own contents - it holds objects. It does implicit free
//of all the contents it holds
void free_scope(scope s);

//this pair contains object
pair scope_find(scope h, string k);
object scope_add(scope h, string k, object v);
object scope_remove(scope h, string k);
object scope_update(scope h, string k, object v);

#endif
