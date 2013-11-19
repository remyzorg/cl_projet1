%{
#include <stdlib.h>
#include "y.tab.h"
%}

%%


[1-9][0-9]*     { yylval.number = atoi(yytext);
                  printf ("Lexer : %d\n", atoi(yytext));
                  return INTEGER;}

[-+*/(){}$] {printf ("%c\n", *yytext); return *yytext;}

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
