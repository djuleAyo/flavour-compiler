%option noyywrap
%option nounput
%option noinput

%{
#include <stdio.h>
#include <stdlib.h>
  void error() {
    printf("greska\n");
    exit(1);
  }

#include "types.h"
#include "ast.h"
#include "parser.tab.h"
%}

%%
int {return INT;}
string return STRING;
print return PRINT;
["].*["] {yylval.s = strdup(yytext); return TXT;}
[a-zA-Z][a-zA-Z0-9_]* {yylval.s = strdup(yytext); return ID;}
[-+*/()[\]{};!=,] return yytext[0];
[-]?[0-9]+ {yylval.i = atoi(yytext); return NUM;}


[ \t\n] ;
. error();

%%
