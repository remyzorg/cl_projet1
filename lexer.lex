%{
#include <stdlib.h>
#include "eval_upmc.h"
#include "y.tab.h"

  extern int yyerror (const char *);
%}

%%

[-+*/(){}$] {return *yytext;}
 
[-]?[0-9]+\.[0-9]+ { yylval.dbl = atof(yytext);
                  return DOUBLE;}

[-]?[0-9]*     { yylval.number = atoi(yytext);
                  return INTEGER;}

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
