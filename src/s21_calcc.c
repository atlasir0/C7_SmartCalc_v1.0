#include "s21_calc.h"

int SmartCalc(const char* input_str, long double* result) {
  Stack_1* s1 = NULL;
  Stack_2* s2 = NULL;
  char* str = (char*)input_str;
  int err = str_ch(str);

  if (*str == '-' || *str == '+') {
    push_val(&s1, 0);
  } else {
    push_val(&s1, 1);
  }

  while (*str && !err) {
    if (isdigit(*str)) {
      push_val(&s1, strtold(str, &str));
    } else {
      if (*str == '(') {
        push_op(&s2, *str, 5);
      } else if (*str == ')') {
        while (s2->oper != '(' && !err) {
          err = calc(&s1, &s2);
        }
        pop_op(&s2);
      } else if (*str != ' ') {
        err = func(&str, &s1, &s2);
      }
      str++;
    }
  }

  if (!err) {
    err = calc_func(&s1, &s2, err, result);
  }

  clear_stack(&s1, &s2);
  return err;
}

int calc_func(Stack_1** s1, Stack_2** s2, int err, long double* res) {
  while (*s2 && !err) {
    err = calc(s1, s2);
  }
  if (!err)
    pop_val(s1, res);
  else
    *res = 0;
  return err;
}

long double performOperation(long double num1, long double num2, char oper) {
  switch (oper) {
    case '+':
      return num1 + num2;
    case '-':
    case '~':
      return num1 - num2;
    case '*':
      return num1 * num2;
    case '/':
      return num1 / num2;
    case '%':
    case 'm':
      return fmodl(num1, num2);
    case '^':
      return powl(num1, num2);
    case 's':
      return sinl(num2);
    case 'c':
      return cosl(num2);
    case 't':
      return tanl(num2);
    case 'S':
      return asinl(num2);
    case 'C':
      return acosl(num2);
    case 'T':
      return atanl(num2);
    case 'l':
      return logl(num2);
    case 'L':
      return log10l(num2);
    case 'q':
      return sqrtl(num2);
    default:
      return 0;
  }
}

int calc(Stack_1** s1, Stack_2** s2) {
  long double n1 = 0, n2 = 0;
  char op = pop_op(s2);
  int err = pop_val(s1, &n2);

  if (strchr("/+-*%^~m", op)) {
    pop_val(s1, &n1);
  }

  if (strchr("qlL", op) && n2 < 0) {
    op = -1;
  }

  if (n2 == 0 && strchr("/%", op)) {
    op = -2;
  }

  if (op > -1) {
    long double result = performOperation(n1, n2, op);
    push_val(s1, result);
  } else {
    err = op;
  }

  return err;
}

int str_ch(const char* str) {
  int err = 0;
  int flag = 0;
  char op = 0;

  if (!strchr("sctalf(-+x", *str) && !isdigit(*str) && *str != '(') {
    return -1;
  }

  while (*str && !err) {
    if (*str != ' ') {
      if (*str == '(') {
        flag++;
      } else if (*str == ')') {
        flag--;
      } else if (!strchr("sincoqrtalmdg.-+x()*/+-%^", *str) && !isdigit(*str)) {
        return -1;
      }

      if (strchr("/*^m)", *str) && strchr("+-(/*m^", op)) {
        return -1;
      } else if (strchr("*", *str) && strchr("(", op)) {
        return -1;
      }

      op = *str;
    }
    str++;
  }

  if (!strchr(")x", *(str - 1)) && !isdigit(*(str - 1))) {
    return -1;
  }

  if (flag != 0) {
    return -1;
  }

  return err;
}

int func(char** str, Stack_1** s1, Stack_2** s2) {
  int err = 0;
  char arith_op = '0';
  char* prov_symbol = *str - 1;
  while (*prov_symbol == ' ') {
    prov_symbol--;
  }
  if ((**str == '-' || **str == '+') && (strchr("+-/*%(d", *prov_symbol))) {
    if (**str == '-') {
      push_val(s1, 0);
      arith_op = '~';
    } else {
      arith_op = '$';
    }
  } else {
    ch_arith_oper(str, &arith_op);
  }
  if (str != NULL && arith_op != '0' && arith_op != '$') {
    int priority = 0, check_priority = 0, step = 0;
    check_priority = peek_prio(s2);
    ch_priority(arith_op, &priority, &step);

    while (check_priority >= priority && check_priority != 5 &&
           check_priority != -1 && !err && priority != 6) {
      err = calc(s1, s2);
      check_priority = peek_prio(s2);
    }
    if (!err) {
      push_op(s2, arith_op, priority);
      *str += step;
    }
  } else if (arith_op != '$') {
    err = -1;
  }
  return err;
}

void ch_priority(char arith_oper, int* priority, int* step) {
  *priority = -1;
  *step = 0;

  switch (arith_oper) {
    case '+':
    case '-':
      *priority = 0;
      break;
    case '*':
    case '/':
      *priority = 1;
      break;
    case '^':
      *priority = 3;
      break;
    case '(':
      *priority = 5;
      break;
    case '~':
      *priority = 6;
      break;
    case 'm':
      *priority = 2;
      *step = 2;
      break;
    case 's':
    case 'c':
    case 't':
    case 'S':
    case 'C':
    case 'T':
    case 'l':
    case 'L':
    case 'q':
      *priority = 4;
      if (strchr("sctL", arith_oper)) {
        *step = 2;
      } else if (strchr("SCTq", arith_oper)) {
        *step = 3;
      } else if (strchr("l", arith_oper)) {
        *step = 1;
      }
      break;
    default:
      break;
  }
}

void ch_arith_oper(char** str, char* arith_oper) {
  if (str != NULL) {
    int num = 3;
    char first_char = **str;
    switch (first_char) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
      case '^':
        *arith_oper = first_char;
        break;
      default:
        if (!strncmp(*str, "ln(", num))
          *arith_oper = 'l';
        else if (!strncmp(*str, "mod", num))
          *arith_oper = 'm';
        else if (!strncmp(*str, "sin(", num++))
          *arith_oper = 's';
        else if (!strncmp(*str, "cos(", num))
          *arith_oper = 'c';
        else if (!strncmp(*str, "tan(", num))
          *arith_oper = 't';
        else if (!strncmp(*str, "log(", num))
          *arith_oper = 'L';
        else if (!strncmp(*str, "asin(", num++))
          *arith_oper = 'S';
        else if (!strncmp(*str, "acos(", num))
          *arith_oper = 'C';
        else if (!strncmp(*str, "atan(", num))
          *arith_oper = 'T';
        else if (!strncmp(*str, "sqrt(", num))
          *arith_oper = 'q';
        else
          *arith_oper = '0';
    }
  }
}
