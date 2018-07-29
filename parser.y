%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

%token PRINT INT STRING
%token<i> NUM
%token<s> ID TXT

%type<n> E stmt stmt_array block

%left '+' '-'
%left '*' '/'

%start program;
%%



program: stmt program  {interpret_stmt($1, main_st);}
|
;

block : '{' stmt_array '}'  { $$ = $2;}
;

stmt_array : stmt stmt_array { add_stmt($2, $1);}
|                            { $$ = Ast_node_block();}
;

stmt: PRINT E ';'      { $$ = Ast_node_un_oper('p', $2); /*interpret_stmt($$, main_st);*/}
| INT  ID '=' E ';'    {$$ = Ast_node_bin_oper('=',Ast_node_id($2), $4);  /*interpret_stmt($$, main_st);*/}
| STRING ID '=' E ';'  {$$ = Ast_node_bin_oper('=', Ast_node_id($2), $4); /*interpret_stmt($$, main_st);*/ }
| block     { /*add_scope(main_st);*/ $$ = $1; /*interpret_stmt($$, main_st);*/}
;


E: E '+' E      { $$ = Ast_node_bin_oper('+', $1, $3);}
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
