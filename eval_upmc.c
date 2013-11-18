


#include "sash.h"

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

void push (char e, char * st, int * i) ;
int pop(char * st, int * i);
void print_stack (char * st, int pt);



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

int parseArithToValue (const char * arith, int size) {

  int start = 2;
  /* int result = 0; */

  /* ops = (char *) malloc(SIZE_STACK); */
  /* numbers = (char *) malloc(SIZE_STACK); */
  
  /* int i = 0; */
  /* for (i = start; i < size - 1; i ++){ */

  /*   if (arith[i] <  */
    
  /*   push(arith[i], numbers, &numbers_pt); */
  /*   push(arith[i], ops, &ops_pt); */
  /* } */
  /* printf("end\n"); */

  /* print_stack(numbers, numbers_pt); */
  

  return 0;
}
