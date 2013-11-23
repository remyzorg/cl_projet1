
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
  case Eq:
  case Ne:
  case Lt:
  case Le:
  case Gt:
  case Ge:
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
    return tmp1 * tmp2;
    break;
  case Div:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    if (tmp2 == 0) {
      printf("Division by zero\n");
    }
    return tmp1 / tmp2;
    break;
  case Eq:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 == tmp2;
    break;
  case Ne:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 != tmp2;
    break;
  case Lt:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 < tmp2;
    break;
  case Le:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 <= tmp2;
    break;
  case Gt:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 > tmp2;
    break;
  case Ge:
    tmp1 = eval(ast->childs.left);
    tmp2 = eval(ast->childs.right);
    return tmp1 >= tmp2;
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
  int val = 0;

  yy_scan_string(arith);
  yylex();

  result = yyparse ();
  
  val = eval(result);
  /* printf("%f\n", val); */

  free_ast(result);
  yylex_destroy();
  

  return val;
}

int is_op(const char* val) {
  return !strcmp(val, "-lt") || !strcmp(val, "-le") || !strcmp(val,"-gt") ||
    !strcmp(val, "-ge") || !strcmp(val, "-eq") || !strcmp(val, "-ne");
}

kind_en get_op(const char* op) {
  if (!strcmp(op, "-lt")) return Lt;
  else if (!strcmp(op, "-le")) return Le;
  else if (!strcmp(op, "-gt")) return Gt;
  else if (!strcmp(op, "-ge")) return Ge;
  else if (!strcmp(op, "-eq")) return Eq;
  else if (!strcmp(op, "-ne")) return Ne;
  else return Nothing;
}

ast_st* eval_args(int argc, const char ** argv, int par, int * index) {

  ast_st *tmp1, *tmp2;
  kind_en op = Nothing;
  int i;

  printf("argc: %d\n", argc);

  for (i = 0; i < argc; i++) {

    printf("arg: %s, i: %d\n", argv[i], i);

    if (!strcmp(argv[i],"(")) {
      printf("Par !\n");
      tmp2 = eval_args(argc-i, argv+i+1, 1, index);
      if (tmp2 == NULL) return NULL;
      printf("i:%d, index: %d\n", i, *index);
      i += *index;
    }
    else if (!strcmp(argv[i], ")"))
      if (par) {
        *index = i+1;
        return tmp1;
      }
      else {
        printf("Closing parenthesis unmatched\n");
        return NULL;
      }

    else if (is_op(argv[i])) { 
      printf("Op !\n");
      op = get_op(argv[i]);
    }

    else {
      int val = !strcmp(argv[i], "") ? 0 : atoi(argv[i]);
      tmp2 = create_int(val);
      
      if (op != Nothing) {
        tmp1 = create_node(op, tmp1, tmp2);
        op = Nothing;
      } else tmp1 = tmp2;
    }
  }

  if (!par)
    return tmp1;
  else {
    printf("Opening parenthesis unmatched\n");
    return NULL;
  }
}


int do_test (int argc, const char ** argv) {

  ast_st* result;
  int *i, val;
  /* char * buffer; */
  
  /* for (i=1; i<argc; i++) size += strlen(argv[i]) + 1;  */
  /* buffer = (char*) malloc(sizeof(char) * size); */

  /* strcat(buffer, argv[1]); */
  /* for (i=2; i<argc; i++) { */
  /*   strcat(buffer, " ");  */
  /*   strcat(buffer, argv[i]); */
  /* } */
  /* printf("result: %s...\n", buffer); */

  /* yy_scan_string(buffer); */
  /* yylex(); */

  /* result = yyparse (); */
  result = eval_args(argc-1, argv+1, 0, i);

  if (result == NULL) return 0;

  val = eval(result);

  printf("%d\n", val);

  free_ast(result);
  /* free(buffer); */
  /* yylex_destroy(); */

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
/*   printf("p=a==f: %f\n", evp); */

/*   printf("m=f>=a: %f \n", evm); */

/* } */
