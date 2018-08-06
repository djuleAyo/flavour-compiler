#ifndef _SCOPE_H
#define _SCOPE_H

#include "flavour.h"
#include "hash.h"
#include "object.h"
#include "basic.h"
/* Module description - scope is hash of names(strings)
   into object.
*/
struct _object;
typedef struct _object* object;

//scope parrent is scope where cur scope is created
//lambda parrent is scope where cur lambda is created

struct _scope {
  //ref_count is number of lambda parrents
  unsigned ref_count;
  hash table;
  struct _scope* lambda_parrent;
  struct _scope* scope_parrent;
};
typedef struct _scope* scope;

extern scope current_scope;
extern scope global_scope;

void init_scope();
void deinit_scope();

//scope knows its own contents - it holds objects. It does implicit free
//of all the contents it holds
scope make_scope(scope scope_parent, scope lambda_parent);
void free_scope(scope s);
void free_scope_branch(scope s);

//scope_find(h, k, t) ==> lookup for lambda, type is for overload
//scope_find(h, k, NULL) ==> lookup for struct or basic type
object scope_find(scope h, string k, type t);
object scope_add(scope h, string k, object o);
object scope_assign(scope h, string k, object o);

#endif
