#pragma once

#include "flavour.h"

typedef enum {
  TYPE_ENUM_INT,
  TYPE_ENUM_STRING
}type_enum;

typedef union
{
    int num;
    string str;
} var_union;

struct _basic_type_value
{
  type_enum type;
  var_union var;
};
typedef struct _basic_type_value* basic_type_value;

basic_type_value Basic_type_value(type_enum t, void* v);


