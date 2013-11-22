%{ /* C declarations used in actions */
 #include <stdio.h>
 #include "eval_upmc.h"

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
%token <dbl> DOUBLE
%token <var> VAR
%union {int number; double dbl; char* var; ast_st *ast;}
%start calcul
 
%type <ast> calcul expr

%%
 /*descriptions of expected inputs       corresponding actions (in C)*/


calcul: expr
| '{' expr '}'      {return $2;}
;


expr   :
  INTEGER                {$$ = create_int($1);}
| DOUBLE                 {$$ = create_float($1);} 
| '$' VAR                { char* r = getenv($2);
                           int i = r==NULL?0:atoi(r);
                           $$ = create_int(i); }
| expr '+' expr          {$$ = create_node(Plus, $1, $3);}
| expr '-' expr          {$$ = create_node(Minus, $1, $3);}
| expr '*' expr          {$$ = create_node(Mult, $1, $3);}
| expr '/' expr          {$$ = create_node(Div, $1, $3);}
| '(' expr ')'           {$$ = $2;}
;


%%                        /* C code */

 /* int main (void) {return yyparse ( );} */




