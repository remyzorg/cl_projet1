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

%left EQ NE
%left LT LE GT GE

%left '+' '-'
%left '*' '/'

%token <number> INTEGER
%token <dbl> DOUBLE
%token <var> VAR
%token EQ NE LT LE GT GE
%union {int number; double dbl; char* var; ast_st *ast;}
%start calcul
 
%type <ast> calcul expr test

%%
 /*descriptions of expected inputs       corresponding actions (in C)*/


calcul: 
'{' expr '}'      {printf ("expr\n"); return $2;}
| test             {printf("test\n"); return $1;}
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

test:
INTEGER                  {printf("%d\n", $1); $$ = create_int($1);}
| test EQ test           {$$ = create_node(Eq, $1, $3);}
| test NE test           {$$ = create_node(Ne, $1, $3);}
| test LT test           {$$ = create_node(Lt, $1, $3);}
| test LE test           {$$ = create_node(Le, $1, $3);}
| test GT test           {$$ = create_node(Gt, $1, $3);}
| test GE test           {$$ = create_node(Ge, $1, $3);}
| '(' test ')'           {$$ = $2;}


%%                        /* C code */

 /* int main (void) {return yyparse ( );} */




