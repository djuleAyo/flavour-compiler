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
