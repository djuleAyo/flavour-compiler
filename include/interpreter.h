#ifndef _interpreter_H
#define _interpreter_H

#include "ast_new.h"

ast_node interpret_expr(ast_node n);
void interpret_stmt(ast_node n);

#endif
