%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_node_macros.h"
#include "flavour.h"
#include "types.h"
#include "ast.h"

#include "sym_table.h"
#include "interpreter.h"

  sym_table main_st = NULL;

  ast_node AST = NULL;
  

  int yylex();
#define yyerror printf
%}


%union {
  int i;
  string s;
  ast_node n;
};

%token PRINT INT STRING WHILE IF ELSE THEN FOR
%token LE GE GT LT EQ NE
%token<i> NUM
%token<s> ID TXT

%type<n> E stmt stmt_array block

%left NE EQ
%left LE GE LT GT
%left '+' '-'
%left '*' '/'

%start program;
%%



program: program stmt  {interpret_stmt($2, main_st);}
|
;

block : '{' stmt_array '}'  { $$ = $2;}
;

stmt_array : stmt_array stmt { add_stmt($1->node.block, $2);}
|                            { $$ = Ast_node_block();}
;

stmt: PRINT E ';'      { $$ = Ast_node_un_oper(OP_PRINT, $2); }
| INT  ID '=' E ';'    {$$ = Ast_node_bin_oper(OP_DEF, Ast_node_id($2), $4);}
| STRING ID '=' E ';'  {$$ = Ast_node_bin_oper(OP_DEF, Ast_node_id($2), $4);}
| block     { $$ = $1; }
| WHILE '(' E ')' stmt {$$ = Ast_node_bin_oper(OP_WHILE, $3, $5);}
| ID '=' E ';'         {$$ = Ast_node_bin_oper(OP_ASSIG, Ast_node_id($1), $3);}
;


E: E '+' E      { $$ = Ast_node_bin_oper('+', $1, $3);}
| E '-' E       { $$ = Ast_node_bin_oper('-', $1, $3);}
| E '*' E       { $$ = Ast_node_bin_oper('*', $1, $3);}
| E '/' E       { $$ = Ast_node_bin_oper('/', $1, $3);}
| '(' E ')'     { $$ = $2;}
| E LT E        { $$ = Ast_node_bin_oper(OP_LT, $1, $3);}
| E GT E        { $$ = Ast_node_bin_oper(OP_GT, $1, $3);}
| E LE E        { $$ = Ast_node_bin_oper(OP_LE, $1, $3);}
| E GE E        { $$ = Ast_node_bin_oper(OP_GE, $1, $3);}
| E EQ E        { $$ = Ast_node_bin_oper(OP_EQ, $1, $3);}
| E NE E        { $$ = Ast_node_bin_oper(OP_NE, $1, $3);}
| ID            { $$ = Ast_node_id($1);}
| NUM           { $$ = Ast_node_con(TYPE_ENUM_INT, &$1);}
| TXT           { $$ = Ast_node_con(TYPE_ENUM_STRING, $1);}
;
%%

int main()
{
  char* a = NULL;
  free(a);
  init_basic_interfaces();

  main_st = Sym_table();
  int aoeu = 3; 
  add_symbol(main_st, "test1", TYPE_ENUM_INT, &aoeu );
  add_symbol(main_st, "test2", TYPE_ENUM_STRING, "aoeu" );  
  

  /*

stmt:
| block                {$$ = Ast_node_block($1);}
;

stmt_array: stmt_array stmt
|
;


block: '{' stmt_array '}' { }
;


arg_array: arg_array ',' tip ID
|tip ID
;
func_dcl: tip ID '(' arg_array ')' block
| tip ID '(' ')' block
;

   */
  yyparse();
  return 0;
}
