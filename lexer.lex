%{
#include <stdlib.h>
#include "y.tab.h"

  extern int yyerror (const char *);
%}

%%

[-+*/(){}$] {return *yytext;}

[1-9][0-9]*     { yylval.number = atoi(yytext);
                  return INTEGER;}
 


[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
