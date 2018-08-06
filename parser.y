%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_node_macros.h"
#include "flavour.h"

extern int yylineno;
extern int yylex();

void yyerror(string msg)
{
    fprintf(stderr,"Error msg: %s\nLine: %d\n", msg, yylineno);
}
%}


%union {
  int i;
  string s;
};

%token PRINT INT STRING WHILE IF ELSE THEN FOR STRUCT
%token LE GE GT LT EQ NE
%token<i> NUM
%token<s> ID TXT


%left NE EQ
%left LE GE LT GT
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%start program;
%%



program: program stmt  {}
|
;

block : '{' stmt_array '}'  {}
;

stmt_array : stmt_array stmt {}
|                            {}
;

def: INT ID '=' E ';'            {}
| STRING ID '=' E ';'            {}
| STRUCT ID '{' decl_array '}'   {}
;

decl_array: decl_array decl  {}
|                            {}
;

decl : INT ID ';'            {}
| STRING ID ';'              {}
| STRUCT ID ID ';'              {}
;

stmt: PRINT  E ';'      {}
| def   {}
| decl  {}
| block                {}
| WHILE '(' E ')' stmt {}
| ID '=' E ';'         {}
| STRUCT ID ID  '{' litteral_array '}' {}
;

litteral_array: litteral        {}
| litteral_array  ',' litteral  {}
;

litteral: '{' litteral_array '}' {}
| NUM                            {}
| TXT                            {}
;


E: E '+' E                  {}
| E '-' E                   {}
| E '*' E                   {}
| E '/' E                   {}
| '(' E ')'                 {}
| E LT E                    {}
| E GT E                    {}
| E LE E                    {}
| E GE E                    {}
| E EQ E                    {}
| E NE E                    {}
| ID                        {}
| NUM                       {}
| '-' NUM %prec UMINUS      {}
| TXT                       {}
;


%%

int main()
{
  /*




  char* a = NULL;
  free(a);
  init_basic_interfaces();

  main_st = Sym_table();
  int aoeu = 3; 
  add_symbol(main_st, "test1", TYPE_ENUM_INT, &aoeu );
  add_symbol(main_st, "test2", TYPE_ENUM_STRING, "aoeu" );  
  
  */
  yyparse();
  
  return 0;
}
