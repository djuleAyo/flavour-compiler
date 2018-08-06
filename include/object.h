#ifndef _OBJECT_H
#define _OBJECT_H

#include "type.h"
#include "flavour.h"
#include "list.h"

#include "basic.h"
#include "struct.h"
#include "lambda.h"


struct _object {
  type type_val;
  void* data;
};

typedef struct _object* object;

/* module - object stores object type name and ptr to value it holds.
 */

//mulitple constructors because every object takes different parameters
//but single unified free. it frees every object type
void free_object(object o);
string object_to_string(object o);

object clone_object(object o);


#endif
