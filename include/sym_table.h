#pragma once

#include "flavour.h"

//dependencies
#include "stack.h"
#include "hash.h"
#include "sym_data.h"


typedef stack sym_table;

//access global scope by sym_table->data[0]
sym_table Sym_table();
void free_sym_table(sym_table st);

hash add_scope(sym_table st);
void end_scope(sym_table st);
void print_scope(hash scope);

void add_symbol(sym_table st, string key, type_enum t, void* var);
pair find_symbol(sym_table st, string key);
//void remove_symbol();



