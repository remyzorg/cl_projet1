%{ /* C declarations used in actions */
 #include <stdio.h>

  extern int yyparse();
  extern int yylex();
  extern int yylineno;
  extern int yytext;

  void yyerror (char *s);

  
  void yyerror (char *s) {
    fprintf (stderr, "Error: '%s' at '%s'\n",
             s, yytext);}
 %}

 /* yacc definitions */

%left '+' '-'
%left '*' '/'
%token <number> INTEGER
%union {int number;}
%start calcul
 
%type<number> calcul expr

%%
 /*descriptions of expected inputs       corresponding actions (in C)*/


calcul: expr
| '{' expr '}'      {return $2;}
;


expr   :
| INTEGER                
| expr '+' expr          {$$ = $1 + $3;}
| expr '-' expr          {$$ = $1 - $3;}
| expr '*' expr          {$$ = $1 * $3;}
| expr '/' expr          {$$ = $1 / $3;}
| '(' expr ')'           {$$ = $2;}
;


%%                        /* C code */

 /* int main (void) {return yyparse ( );} */




