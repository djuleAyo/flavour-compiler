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

//arguments takes 1 node for basic type and node contains
//void* ptr to int or void* ptr to dynamicaly allocated string

//if t is composite arguments take list of objects
//args must be objects to do semantical analisis (remember types
// in those objects)

//if t is func then arguments are func args - objects
void* object_initialize(type t, list arguments);



#endif
