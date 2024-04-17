#include "smart_calc.h"

int is_operation(char symbol) {
  int result = 0;
  if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||
      symbol == '^')
    result = 1;
  return result;
}

int is_function(char symbol) {
  int result = 0;
  if (symbol == 's' || symbol == 'a' || symbol == 'c' || symbol == 't' ||
      symbol == 'l')
    result = 1;
  return result;
}

int get_priority(char symbol) {
  int result = 0;
  if (symbol == '(' || symbol == ')') {
    result = BRACKET;
  } else if (symbol == '+' || symbol == '-') {
    result = PLUSMINUS;
  } else if (symbol == '*' || symbol == '/' || symbol == 'm') {
    result = MULTDIVMOD;
  } else if (symbol == '^') {
    result = POW;
  } else if (is_function(symbol)) {
    result = FUNCTION;
  }
  return result;
}

void calculate_operation(stack_double **number_stack, char *operation) {
  double num1, num2;
  double result = 0;
  num2 = pop_double(number_stack);
  num1 = *number_stack ? pop_double(number_stack) : 0;
  result = num2;
  if (operation[0] == '+') {
    result = num1 + num2;
  } else if (operation[0] == '-') {
    result = num1 - num2;
  } else if (operation[0] == '*') {
    result = num1 * num2;
  } else if (operation[0] == '/') {
    result = num1 / num2;
  } else if (operation[0] == 'm') {
    result = fmod(num1, num2);
  } else if (operation[0] == '^') {
    result = powf(num1, num2);
  }
  push_double(number_stack, result);
}

void calculate_function(stack_double **number_stack, char *operation) {
  double result = 0;
  double num = pop_double(number_stack);
  if (!strcmp(operation, "cos")) {
    result = cos(num);
  } else if (!strcmp(operation, "sin")) {
    result = sin(num);
  } else if (!strcmp(operation, "tan")) {
    result = tan(num);
  } else if (!strcmp(operation, "acos")) {
    result = acos(num);
  } else if (!strcmp(operation, "asin")) {
    result = asin(num);
  } else if (!strcmp(operation, "atan")) {
    result = atan(num);
  } else if (!strcmp(operation, "sqrt")) {
    result = sqrt(num);
  } else if (!strcmp(operation, "ln")) {
    result = log(num);
  } else if (!strcmp(operation, "log")) {
    result = log10(num);
  }
  push_double(number_stack, result);
}