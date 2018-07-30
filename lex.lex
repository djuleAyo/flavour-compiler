%option noyywrap
%option nounput
%option noinput
%option yylineno

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
while return WHILE;

for return FOR;

if return IF;
then return THEN;
else return ELSE;

"<=" return LE;
">=" return GE;
"==" return EQ;
"<" return LT;
">" return GT;
"!=" return NE;

int return INT;
string return STRING;

print return PRINT;

["].*["] {yylval.s = NULL; /*strdup(yytext);*/ return TXT;}
[a-zA-Z][a-zA-Z0-9_]* {yylval.s =NULL;/* strdup(yytext);  */return ID;}
[-+*/()[\]{};!=,><] return yytext[0];
[0-9]+ {yylval.i = atoi(yytext); return NUM;}


[ \t\n] ;
. error();

%%
