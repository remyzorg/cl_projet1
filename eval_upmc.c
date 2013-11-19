


#include "sash.h"
#include "y.tab.h"

#define SIZE_STACK 100

enum kind_en {Nothing, Plus, Minus, Mult, Div, Integer, Real};

typedef struct ast_st {
  enum kind_en en;
  union {
    struct ast_st *left, *right;
    int num;
    double flo;
  };
} ast_st;


int parseArithToValue (const char * arith) {


  printf("Eval entry : %s\n", arith);
  yy_scan_string(arith);
  yylex();


  printf("Eval result : %d\n", yyparse ());
  yylex_destroy();
  

  return 0;
}
