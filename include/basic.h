#ifndef _BASIC_H
#define _BASIC_H

#include "object.h"
#include "flavour.h"

struct _object;
typedef struct _object* object;

typedef object basic_object;

basic_object make_int_object(int x);
basic_object make_string_object(string s);

basic_object clone_int_object(object o);
basic_object clone_string_object(object o);

void free_int_object(object o);
void free_string_object(object o);

string int_object_to_string(object o);
string string_object_to_string(object o);
#endif
