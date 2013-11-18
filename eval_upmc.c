


#include "sash.h"



enum kind_en {Nothing, Plus, Minus, Mult, Div, Integer, Real};

typedef struct ast_st {
  enum kind_en en;
  union {
    struct ast_st *left, *right;
    int num;
    double flo;
  };
} ast_st;



