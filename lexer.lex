%{
#include <stdlib.h>
#include "y.tab.h"
%}

%%



[1-9][0-9]* {return INTEGER;}

[-()<>=+*/;{}.$] {return *yytext;}

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");

%%

int yywrap(void) {
    return 1;
}
