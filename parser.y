%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_node_macros.h"
#include "ast_new.h"
#include "flavour.h"
#include "scope.h"
#include "type.h"
#include "interpreter.h"

  extern int yylineno;
extern int yylex();

#define exe_global($$) do{if(current_scope == global_scope)    \
      interpret_stmt($$); } while (0)

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

%type <ast> E stmt block stmt_array def


%left NE EQ
%left LE GE LT GT
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%left '.'

%start program;
%%



program: program stmt  {interpret_stmt($2);}
|
;

block : '{' stmt_array '}'  {$$ = $2;}
;

stmt_array : stmt_array stmt {add_to_block($1, $2); }
|                            {
  $$ = make_ast_block();


 }
;

stmt: PRINT  E ';'      {$$ = ast_print($2);}
| def                  {$$ = $1;}
| block                {
  $$ = $1;
}
| WHILE '(' E ')' stmt {$$ = ast_while($3, $5);}
| IF '(' E ')' stmt    {}
| ID '=' E ';'         {$$ = ast_bin_node(ast_id($1), $3, AST_NODE_ASSIG);}
;

def: INT ID '=' E ';'            {
  $$ = ast_bin_node(ast_id($2), $4, AST_NODE_DEF);
 }
;

E: E '+' E                  {$$ = ast_bin_node($1, $3, AST_NODE_OP_PLUS);}
| E '-' E                   {$$ = ast_bin_node($1, $3, AST_NODE_OP_MINUS);}
| E '*' E                   {$$ = ast_bin_node($1, $3, AST_NODE_OP_MUL);}
| E '/' E                   {$$ = ast_bin_node($1, $3, AST_NODE_OP_DIV);}
| '(' E ')'                 {$$ = $2;}
| E LT E                    {$$ = ast_bin_node($1, $3, AST_NODE_OP_LT);}
| E GT E                    {$$ = ast_bin_node($1, $3, AST_NODE_OP_GT);}
| E LE E                    {$$ = ast_bin_node($1, $3, AST_NODE_OP_LE);}
| E GE E                    {$$ = ast_bin_node($1, $3, AST_NODE_OP_GE);}
| E EQ E                    {$$ = ast_bin_node($1, $3, AST_NODE_OP_EQ);}
| E NE E                    {$$ = ast_bin_node($1, $3, AST_NODE_OP_NE);}
| NUM                       {$$ = ast_int_con($1);}
| TXT                       {$$ = ast_string_con($1);}
| '-' E %prec UMINUS        {$$ = ast_un_node($2, AST_NODE_OP_UN_MINUS);}
| ID                        {$$ = ast_id($1);}
| ID '.' ID                 {}
;


%%

int main()
{
  init_basic_types();
  init_scope();
  /*

    | STRING ID '=' E ';'            {}
    | STRUCT ID '{' decl_array '}'   {}
    ;



    decl_array: decl_array decl  {}
    |                            {}
    ;

    | decl                 {}
    ;


    type: INT
    |STRING
    |STRUCT ID
    ;

    litteral: '{' litteral_array '}' {}

    ;
    litteral_array: litteral        {}
    | litteral_array  ',' litteral  {}
    ;



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
