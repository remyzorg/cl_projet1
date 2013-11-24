%{
#include <stdlib.h>
#include "eval_upmc.h"
#include "y.tab.h"

  extern int yyerror (const char *);
%}

%%



[-+*/(){}$] {return *yytext;}
 
[-]?[0-9]+\.[0-9]+      { yylval.dbl = atof(yytext);
                          return DOUBLE;}

[-]?[0-9]*              { yylval.number = atoi(yytext);
                          return INTEGER;}

([A-Z]|[_])+            { yylval.var = yytext;
                          return VAR;}

"-test"                 { return TEST; }
"-a"                    { return AND; }
"-o"                    { return OR; }
"-eq"                   { return EQ; }
"-ne"                   { return NE; }
"-lt"                   { printf("%s\n", yytext); return LT; }
"-le"                   { return LE; }
"-gt"                   { return GT; }
"-ge"                   { return GE; }

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
