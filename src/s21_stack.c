#include "s21_stack.h"

void push_val(Stack_1 **top, long double value) {
  Stack_1 *Op = (Stack_1 *)malloc(sizeof(Stack_1));
  Op->value = value;
  Op->next = *top;
  *top = Op;
}
void push_op(Stack_2 **top, char oper, int priority) {
  Stack_2 *Op = (Stack_2 *)malloc(sizeof(Stack_2));
  Op->oper = oper;
  Op->priority = priority;
  Op->next = *top;
  *top = Op;
}

int pop_val(Stack_1 **top, long double *value) {
  int err = 0;
  if (*top) {
    Stack_1 *nd = *top;
    *top = (*top)->next;
    *value = nd->value;
    free(nd);
  } else
    err = -1;
  return err;
}

int pop_op(Stack_2 **top) {
  int priority;
  if (*top) {
    Stack_2 *nd = *top;
    *top = (*top)->next;
    priority = nd->oper;
    free(nd);
  } else
    priority = -1;
  return priority;
}

int peek_prio(Stack_2 **top) {
  int priority;
  if (*top) {
    priority = (*top)->priority;
  } else
    priority = -1;
  return priority;
}
void clear_stack(Stack_1 **Stack_1, Stack_2 **Stack_2) {
  long double clear;
  while (*Stack_1) pop_val(Stack_1, &clear);
  while (*Stack_2) pop_op(Stack_2);
}