#ifndef _OBJECT_H
#define _OBJECT_H

#include "type.h"
#include "flavour.h"
#include "list.h"

struct _object {
  type type_val;
  void* data;
};

typedef struct _object* object;

/* module - object stores object type name and ptr to value it holds.
 */

object make_object(type t, list arguments);
void free_object(object o);
void* object_initialize(type t, list arguments);



#endif
