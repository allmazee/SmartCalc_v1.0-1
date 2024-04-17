#include "smart_calc.h"

double get_result(double x, char *str) {
  double result = 0;
  char **tokens = (char **)malloc(STACK_MAX_SIZE * sizeof(char *));
  if (tokens) {
    for (int i = 0; i < STACK_MAX_SIZE; i++) {
      tokens[i] = (char *)malloc(STACK_MAX_SIZE * sizeof(char));
    }
  }
  int length = parser(str, tokens);
  if (length != OUT_OF_TOKENS && length != NAN_OPERAND) {
    stack_double *double_stack = NULL;
    stack_str *str_stack = NULL;
    result = polish_notation(&double_stack, &str_stack, tokens, length, x);
    clear_str(&str_stack);
    clear_double(&double_stack);
  } else
    result = NAN;
  for (int i = 0; i < STACK_MAX_SIZE; i++) {
    free(tokens[i]);
  }
  free(tokens);
  return result;
}

double polish_notation(stack_double **number_stack, stack_str **operation_stack,
                       char **tokens, int length, double x) {
  double result = 0;
  int priority, prev_priority;
  char operation[5], prev_operation[5];
  for (int i = 0; i < length; i++) {
    char symbol = tokens[i][0];
    if (isdigit(symbol)) {
      char *endptr;
      push_double(number_stack, strtod(tokens[i], &endptr));
    } else if (symbol == 'x') {
      push_double(number_stack, x);
    } else {
      strcpy(operation, tokens[i]);
      priority = get_priority(symbol);
      if (!(*operation_stack) || symbol == '(') {
        if ((symbol == '(' && is_operation(tokens[i + 1][0]))) {
          push_double(number_stack, 0);
        }
        push_str(operation_stack, operation, priority);
      } else if (symbol == ')') {
        while (*operation_stack) {
          pop_str(operation_stack, operation);
          if (operation[0] == '(') break;
          calculate_operation(number_stack, operation);
        }
        if (*operation_stack) {
          strcpy(prev_operation, peek_str(*operation_stack));
          if (is_function(prev_operation[0])) {
            pop_str(operation_stack, operation);
            calculate_function(number_stack, operation);
          }
        }
      } else {
        operation_process(number_stack, operation_stack, operation,
                          prev_operation, &priority, &prev_priority);
      }
    }
  }
  result = pop_all(number_stack, operation_stack, operation);
  return result;
}

void operation_process(stack_double **number_stack, stack_str **operation_stack,
                       char *operation, char *prev_operation, int *priority,
                       int *prev_priority) {
  strcpy(prev_operation, peek_str(*operation_stack));
  *prev_priority = get_priority(prev_operation[0]);
  if (*priority > *prev_priority || (*priority == 3 && *prev_priority == 3)) {
    push_str(operation_stack, operation, *priority);
  } else {
    while (*priority <= *prev_priority && *operation_stack) {
      pop_str(operation_stack, prev_operation);
      if (*number_stack) calculate_operation(number_stack, prev_operation);
      if (*operation_stack) {
        strcpy(prev_operation, peek_str(*operation_stack));
        *prev_priority = get_priority(prev_operation[0]);
      }
    }
    push_str(operation_stack, operation, *priority);
  }
}

double pop_all(stack_double **number_stack, stack_str **operation_stack,
               char *operation) {
  double result = 0;
  while (*operation_stack) {
    pop_str(operation_stack, operation);
    if (*number_stack) {
      (is_function(operation[0]))
          ? calculate_function(number_stack, operation)
          : calculate_operation(number_stack, operation);
    }
  }
  if (*number_stack) result = pop_double(number_stack);
  return result;
}
