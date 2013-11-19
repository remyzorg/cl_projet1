%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* prototypes */
%}

%token <int> INTEGER
%token <char> VARIABLE

%left '+' '-'
%left '*' '/'

%start program
%%

program:
        expr                { exit(0); }
        ;


expr:
          INTEGER               { $$ = $1; }
        /* | VARIABLE              { $$ = id($1); } */
        | expr '+' expr         { $$ = $1 + $3; }
        | expr '-' expr         { $$ = $1 - $3; }
        | expr '*' expr         { $$ = $1 * $3; }
        | expr '/' expr         { $$ = $1 / $3); }
        | '(' expr ')'          { $$ = $2; }
        ;
%%

/* int main(void) { */
/*     yyparse(); */
/*     return 0; */
/* } */

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}
