#pragma once
#include "basic_interface.h"
#include "types.h"
#include "object.h"

typedef union
{
  type type_val;
  object object_val;
}sym_data_union;

typedef enum {SYM_DATA__TYPE, SYM_DATA__FUNC, SYM_DATA__OBJ, SYM_DATA__CLASS} type_of_sym_data;

struct _sym_data
{
  type_of_sym_data type;
  sym_data_union data_union;
};

typedef struct _sym_data* sym_data;

sym_data make_sym_data(sym_data_union u, void* data);


void free_sym_data(sym_data s);
