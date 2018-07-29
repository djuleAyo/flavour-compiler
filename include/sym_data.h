#pragma once
#include "basic_interface.h"
#include "types.h"

struct _sym_data
{
  basic_type_value type_value;
  basic_interface bi;
};

typedef struct _sym_data* sym_data;

//TODO symbol constructor for user defined type (object)
//symbol Symbol(type_enum t, void* var, basic_interface bi);
sym_data Sym_data(type_enum t, void* var);

//TODO za diskusiju da li da cuvamo type kao string
//zbog objekata koje moze definisati programer
/*
 typedef string type;
symbol SymbolUserDefined(  ,void* var, string (*toString)(void*), void (*destructor)(void*));
*/


void free_sym_data(sym_data s);

// "type value" = symbolToString
string sym_dataToString(sym_data s);
int type_check(sym_data s, type_enum t);
int same_type(sym_data s1, sym_data s2);
