#ifndef _STRUCT_H
#define _STRUCT_H

#include "object.h"

struct _object;
typedef struct _object* object;
typedef object struct_object;


struct_object make_struct(type t, list arguments);
void free_struct(struct_object o);
struct_object clone_struct(struct_object o);

string struct_to_string(struct_object o);

object operator_dot(struct_object o, string propertie);

#endif
