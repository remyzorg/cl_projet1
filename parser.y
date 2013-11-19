%{ /* C declarations used in actions */
 #include <stdio.h>
  int yyparse();
  int yylex();
  void yyerror (char *s) {printf ("Fat erreur : %s\n", s);}
 %}

 /* yacc definitions */

%left '+' '-'
%left '*' '/'
%token <number> INTEGER
%union {int number;}
%start expr
 
%type<number> calcul expr

%%
 /*descriptions of expected inputs       corresponding actions (in C)*/


calcul:
| '$' '{' expr '}'       { $$ = $3;}
;

expr   :
| INTEGER                { printf("Parser : %d", $1); $$ = $1;}
| expr '+' expr          {$$ = $1 + $3;}
| expr '-' expr          {$$ = $1 - $3;}
| expr '*' expr          {$$ = $1 * $3;}
| expr '/' expr          {$$ = $1 / $3;}
| '(' expr ')'           {$$ = $2;}
;


%%                        /* C code */

 /* int main (void) {return yyparse ( );} */




