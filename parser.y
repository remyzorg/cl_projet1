%{ /* C declarations used in actions */
 #include <stdio.h>

  extern int yyparse();
  extern int yylex();
  extern int yylineno;
  extern int yytext;

  void yyerror (char *s);

  
  void yyerror (char *s) {
    fprintf (stderr, "%d: error: '%s' at '%d'\n",
             yylineno, s, yytext);}
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
| '$' expr       {printf("Parser : %d", $2); return $2;}
;


expr   :
| INTEGER                
| expr '+' expr          {printf("calcuuul : %d\n", $1 + $3); $$ = $1 + $3;}
| expr '-' expr          {$$ = $1 - $3;}
| expr '*' expr          {$$ = $1 * $3;}
| expr '/' expr          {$$ = $1 / $3;}
| '(' expr ')'           {$$ = $2;}
;


%%                        /* C code */

 /* int main (void) {return yyparse ( );} */




