%{ /* C declarations used in actions */
 #include <stdio.h>
  int yyparse();
  int yylex();
 void yyerror (char *s) {fprintf (stderr, "%s\n", s);}
 %}

 /* yacc definitions */

%left '+' '-'
%left '*' '/'
%token <a_number> INTEGER
%union {int a_number;}
%start expr
 
%type<a_number> expr

%%
 /*descriptions of expected inputs       corresponding actions (in C)*/

expr   :  INTEGER                         { return $1; }
        | expr '+' expr                   {$$ = $1 + $3;}
        | expr '-' expr                   {$$ = $1 - $3;}
        | expr '*' expr                   {$$ = $1 * $3;}
        | expr '/' expr                   {$$ = $1 / $3;}
        | '(' expr ')'                    {$$ = $2;}
        | '$' '{' expr '}'                    {$$ = $3;}
        ;


 %%                        /* C code */

 /* int main (void) {return yyparse ( );} */




