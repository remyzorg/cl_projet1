


#include "sash.h"
#include "y.tab.h"

#define SIZE_STACK 100

typedef enum kind_en {Nothing, Plus, Minus, Mult, Div, Integer, Real} kind_en;

typedef struct ast_st {
  enum kind_en en;
  union {
    struct ast_st *left, *right;
    int num;
    double flo;
  };
} ast_st;

void push (char e, char * st, int * i) ;
int pop(char * st, int * i);
void print_stack (char * st, int pt);
void free_ast(ast_st* a);
ast_st* create_int(int value);
ast_st* create_float(double value);
ast_st* create_node(kind_en op, ast_st* left, ast_st* right);


void free_ast(ast_st* a) {

  switch(a->en) {

  case Plus:
  case Minus:
  case Mult:
  case Div:
    free_ast(a->left);
    free_ast(a->right);
    free(a);
    break;

  case Integer:
  case Real:
    free(a);
    break;

  default: break;
  }

}


/* Creates a integer node */
ast_st* create_int(int value) {
  ast_st *a;

  if ((a = (ast_st*) malloc(sizeof(ast_st))) == NULL) {
    exit(1);
  }

  a->num = value;
  a->en = Integer;

  return a;

}

/* Creates a floating point number node */
ast_st* create_float(double value) {

  ast_st *a;

  if ((a = (ast_st*) malloc(sizeof(ast_st))) == NULL) {
    exit(1);
  }

  a->flo = value;
  a->en = Real;

  return a;

} 

/* Creates an ast node from the given operation and the two child nodes */
ast_st* create_node(kind_en op, ast_st* left, ast_st* right) {

  ast_st *a;

  if ((a = (ast_st*) malloc(sizeof(ast_st))) == NULL) {
    free_ast(left);
    free_ast(right);
    exit(1);
  }

  a->left = left;
  a->right = right;
  a->en = op;

  return a;
}



char * ops;
char * numbers;
int ops_pt = -1;
int numbers_pt = -1;

void push (char e, char * st, int * i) {
  if(*i==(SIZE_STACK-1))
    {
      printf("\n Stack overflow");
      return;
    }
  else
    {
      st[++(*i)] = e;
    }
}

int pop(char * st, int * i)
{
  if(*i==-1)
    {
      printf("\n Stack underflow");
      return -1;
    }
  else
    {
      return st[(*i)--];
    }
}

int opcompare (char c1, char c2);
int valueop (char c);

void print_stack (char * st, int pt){
  int i = 0;
  for (i = 0; i <= pt; i++)
    printf("%c ", st[i]);
}

int valueop (char c){
  if (c == '/' || c == '*')
    return 1;
  else return 0;
}

int opcompare (char c1, char c2){
  if (valueop (c1) > valueop (c1))
    return 1;
  else if (valueop (c1) < valueop (c1))
    return -1;
  else return 0;
}

int parseArithToValue (const char * arith) {

  yy_scan_string("${5}");
  yylex();


  printf("ici result : %d\n", yyparse ());
  yylex_destroy();
  

  return 0;
}
