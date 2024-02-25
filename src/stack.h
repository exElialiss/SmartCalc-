#ifndef STACK_H
#define STACK_H

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MEMORY_ERROR 2
#define SYNTAX_ERROR 1

typedef enum status { number, x_status, operator_status, function } status;

typedef enum priority {
  l_brack_pr = 0,
  sum_pr = 1,
  sub_pr = 1,
  mul_pr = 2,
  div_pr = 2,
  pow_pr = 3,
  mod_pr = 3,
  u_sum_pr = 5,
  u_sub_pr = 5,
  r_brack_pr = 6
} priority;

typedef struct lexem {
  int priority;
  int status;
  double value;
  char name[3];
} lexem;

typedef struct stack {
  int size;
  struct stack *last_lexem;
  lexem current_lexem;
} stack;

void init_lexem(lexem *lexem, int status, double value, char *name);
int get_priority(char symbol);
stack *init_stack();
stack *pointer_elem(lexem lexem);
stack *push(stack *head, lexem lexem);
lexem pop(stack **head);
void free_stack(stack *head);

#endif  // STACK_H