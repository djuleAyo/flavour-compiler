#pragma once

#include "ast.h"
#include "flavour.h"
#include "sym_table.h"
#include "types.h"

basic_type_value interpret_expr(ast_node n, sym_table st);

