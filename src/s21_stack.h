#ifndef S21_STACK_H
#define S21_STACK_H

#include <stdlib.h>

typedef struct Stack_1 {
  long double value;
  struct Stack_1 *next;
} Stack_1;

typedef struct Stack_2 {
  char oper;
  int priority;
  struct Stack_2 *next;
} Stack_2;

void push_val(Stack_1 **top, long double value);
void push_op(Stack_2 **top, char oper, int priority);
int pop_val(Stack_1 **top, long double *value);
int pop_op(Stack_2 **top);
int peek_prio(Stack_2 **top);
#endif