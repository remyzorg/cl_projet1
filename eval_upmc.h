#ifdef _EVAL_UPMC_H_

#else

#define _EVAL_UPMC_H_
typedef enum kind_en {Nothing, Plus, Minus, Mult, Div, Integer, Real} kind_en;

typedef struct ast_st ast_st;

typedef struct node {
  ast_st *left, *right;
} node;

struct ast_st {
  enum kind_en en;
  union {
    node childs;
    int num;
    double flo;
  };
};


void push (char e, char * st, int * i) ;
int pop(char * st, int * i);
void print_stack (char * st, int pt);
void free_ast(ast_st* a);
ast_st* create_int(int value);
ast_st* create_float(double value);
ast_st* create_node(kind_en op, ast_st* left, ast_st* right);
double eval(ast_st* ast);
int parseArithToValue (const char * arith);

#endif
