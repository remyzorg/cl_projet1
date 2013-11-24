%{ /* C declarations used in actions */
 #include <stdio.h>
 #include "eval_upmc.h"
 #include "y.tab.h"

  extern int yyparse();
  extern int yylex();
  extern int yylineno;
  extern int yytext;

  void yyerror (char *s);

  ast_st* result = NULL;
  
  void yyerror (char *s) {
    fprintf (stderr, "Error: '%s' at '%s'\n", s, yytext);}
 %}

 /* yacc definitions */

%left AND OR
%left EQ NE
%left LT LE GT GE

%left '+' '-'
%left '*' '/'

%token <number> INTEGER
%token <dbl> DOUBLE
%token <var> VAR
%token EQ NE LT LE GT GE AND OR TEST
%union {int number; double dbl; char* var; ast_st *ast;}
%start calcul
 
%type <ast> calcul expr test

%%
 /*descriptions of expected inputs       corresponding actions (in C)*/


calcul: 
 '{' expr '}'          {printf ("expr\n"); result = $2;}
| TEST test             {printf("test\n"); result = $2;}
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
| test AND test          {printf("Test and\n"); $$ = create_node(And, $1, $3);}
| test OR test           {printf("Test or\n"); $$ = create_node(Or, $1, $3);}
| test EQ test           {printf("Test eq\n"); $$ = create_node(Eq, $1, $3);}
| test NE test           {printf("Test ne\n"); $$ = create_node(Ne, $1, $3);}
| test LT test           {printf("Test lt\n"); $$ = create_node(Lt, $1, $3);}
| test LE test           {printf("Test le\n"); $$ = create_node(Le, $1, $3);}
| test GT test           {printf("Test gt\n"); $$ = create_node(Gt, $1, $3);}
| test GE test           {printf("Test ge\n"); $$ = create_node(Ge, $1, $3);}
| '(' test ')'           {$$ = $2;}
;

%%                       

