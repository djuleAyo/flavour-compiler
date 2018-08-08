%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_node_macros.h"
#include "ast_new.h"
#include "flavour.h"

extern int yylineno;
extern int yylex();

 init_basic_types();
 init_scope();

void yyerror(string msg)
{
    fprintf(stderr,"Error msg: %s\nLine: %d\n", msg, yylineno);
}
%}


%union {
  int i;
  string s;
  ast_node ast;
};

%token PRINT INT STRING WHILE IF ELSE THEN FOR STRUCT
%token LE GE GT LT EQ NE
%token<i> NUM
%token<s> ID TXT

%type<ast> litteral E


%left NE EQ
%left LE GE LT GT
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%left '.'

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

decl : type ID ';'     {}

stmt: PRINT  E ';'      {printf("%d", $2->data.int_con);}
| def   {}
| decl  {}
| block                {printf("block\n");}
| WHILE '(' E ')' stmt {}
| IF '(' E ')' stmt    {}
| ID '=' E ';'         {}
| STRUCT ID ID  '{' litteral_array '}' {}
;

litteral_array: litteral        {}
| litteral_array  ',' litteral  {}
;

litteral: '{' litteral_array '}' {}
| NUM                            {$$ = ast_int_con($1);}
| TXT                            {}
;

type: INT
|STRING
|STRUCT ID
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
| litteral                  {$$ = $1;}
| '-' E %prec UMINUS        {}
| ID                        {}
| ID '.' ID                 {}
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
