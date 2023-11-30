#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_stack.h"


int SmartCalc(const char* input_str, long double* result);
int SmartCalc_X(const char* input_str, long double* result, long double x);
int calc(Stack_1** top_1, Stack_2** top_2);
int str_ch(const char* str); 
int func(char** str, Stack_1** Stack1_1, Stack_2** Stack_2);
void ch_priority(char arith_oper, int* priority, int* step);
void ch_arith_oper(char** str, char* arith_oper);
int calc_func(Stack_1** Stack_1, Stack_2** Stack_2, int error,
           long double* result);
void clear_stack(Stack_1** Stack_1, Stack_2** Stack_2); 
#endif
