%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flavour.h"
#include "types.h"
#include "ast.h"

#include "sym_table.h"

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

%token PRINT INT STRING
%token<i> NUM
%token<s> ID TXT

%type<n> E stmt block program stmt_array

%left '+' '-'
%left '*' '/'

%start program;
%%

program: program  E ';' { print_ast_node($1); }
|
;


E: E '+' E      { $$ = Ast_node_bin_oper('-', $1, $3);}
| E '-' E       { $$ = Ast_node_bin_oper('-', $1, $3);}
| E '*' E       { $$ = Ast_node_bin_oper('*', $1, $3);}
| E '/' E       { $$ = Ast_node_bin_oper('/', $1, $3);}
| '(' E ')'     { $$ = $2;}
| ID            { $$ = Ast_node_id($1);}
| NUM           { $$ = Ast_node_con(TYPE_ENUM_INT, &$1);}
| TXT           { $$ = Ast_node_con(TYPE_ENUM_STRING, $1);}
;
%%

int main()
{
  main_st = Sym_table();
  init_basic_interfaces();
  /*

stmt: PRINT E ';'      {}
| INT  ID '=' E ';'    {$$ = Ast_node_bin_oper('=',Ast_node_id($2), $3);}
| STRING ID '=' E ';'  {$$ = Ast_node_bin_oper('=',Ast_node_id($2), $3);}
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
