#include "s21_calc.h"
int SmartCalc_X(const char* input_str, long double* result, long double x) {
  Stack_1* operand_stack = NULL;
  Stack_2* operator_stack = NULL;
  int open_paren_count = 0;
  int close_paren_count = 0;
  char* current_char = (char*)input_str;
  int error = str_ch(current_char);
  int operator_count = 0;

  if (strchr(current_char, 'x') == NULL) {
    return -1;
  }
  push_val(&operand_stack, 1);
  if (*current_char == '-' || *current_char == '+') {
    push_val(&operand_stack, 0);
  }
  while (*current_char != '\0' && !error) {
    if (isdigit(*current_char)) {
      long double num = strtold(current_char, &current_char);
      push_val(&operand_stack, num);
    } else {
      if (*current_char == '(') {
        push_op(&operator_stack, *current_char, 5);
        open_paren_count++;
      } else if (*current_char == ')') {
        while (operator_stack->oper != '(' && !error)
          error = calc(&operand_stack, &operator_stack);
        pop_op(&operator_stack);
        close_paren_count++;
        if (close_paren_count > open_paren_count) {
          return -1;
        }
      } else if (*current_char != ' ') {
        if (*current_char != 'x') {
          error = func(&current_char, &operand_stack, &operator_stack);
          operator_count++;
        } else {
          push_val(&operand_stack, x);
        }
      }
      current_char++;
    }
  }

  if (open_paren_count != close_paren_count) {
    return -1;
  }

  if (operator_count == 0) {
    return -1;
  }

  if (!error) {
    error = calc_func(&operand_stack, &operator_stack, error, result);
  }

  clear_stack(&operand_stack, &operator_stack);
  return error;
}
