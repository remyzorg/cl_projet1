
#include <stdlib.h>
#include <stdio.h>
#include "sash.h"
#include "eval_upmc.h"
#include "y.tab.h"


#define SIZE_STACK 100

void free_ast(ast_st* a) {

  switch(a->en) {

  case Plus:
  case Minus:
  case Mult:
  case Div:
    free_ast(a->childs.left);
    free_ast(a->childs.right);
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
  

  a->childs.left = left;
  a->childs.right = right;
  a->en = op;

  return a;
}

double eval(ast_st* ast) {

  double tmp1, tmp2;

  switch (ast->en) {
  case Real:
    return ast->flo;
    break;
  case Integer:
    return (double) ast->num;
    break;
  case Plus:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 + tmp2;
    break;
  case Minus:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 - tmp2;
    break;
  case Mult:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 + tmp2;
    break;
  case Div:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 + tmp2;
    break;
  default:
    return 0.;
    break;
  }

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

  ast_st* result;
  double val = 0;

  yy_scan_string(arith);
  yylex();

  result = yyparse ();
  val = eval(result);
  
  free_ast(result);
  yylex_destroy();
  

  return val;
}


/* int main(char **argc, int argv) { */

/*   ast_st* a = create_int(2); */
/*   ast_st* f = create_float(4.0); */

/*   ast_st* p = create_node(Plus, a, f); */

/*   ast_st* m = create_node(Minus, p, a); */

/*   int eva = eval(a); */
/*   double evf = eval(f); */
/*   double evp = eval(p); */
/*   double evm = eval(m); */

/*   printf("a: %d\n", eva); */
/*   printf("f: %f\n", evf); */
/*   printf("p=a+f: %f\n", evp); */

/*   printf("m=f-a: %f \n", evm); */

/* } */
