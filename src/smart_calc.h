#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX_SIZE 256

#define OUT_OF_TOKENS -2
#define NAN_OPERAND -1

#define BRACKET 0
#define PLUSMINUS 1
#define MULTDIVMOD 2
#define POW 3
#define FUNCTION 4

typedef struct stack_double {
  double value;
  struct stack_double *next;
} stack_double;

typedef struct stack_str {
  char value[5];
  int priority;
  struct stack_str *next;
} stack_str;

// STACK
void push_double(stack_double **head, double value);
double pop_double(stack_double **head);
double peek_double(stack_double *head);
void clear_double(stack_double **head);

void push_str(stack_str **head, char *value, int priority);
void pop_str(stack_str **head, char *buff);
char *peek_str(stack_str *head);
void clear_str(stack_str **head);

// PARSER
int parser(char *str, char **tokens);
int nan_finder(char *str);
int nan_digit(char *str, int *i);
int nan_function(char *str, int *i);
int nan_trigonometric(char *str, int *i);

// SMART CALC
double get_result(double x, char *str);
double polish_notation(stack_double **number_stack, stack_str **operation_stack,
                       char **tokens, int length, double x);
void operation_process(stack_double **number_stack, stack_str **operation_stack,
                       char *operation, char *prev_operation, int *priority,
                       int *prev_priority);
double pop_all(stack_double **number_stack, stack_str **operation_stack,
               char *operation);

// OTHER
int is_operation(char symbol);
int is_function(char symbol);
int get_priority(char symbol);
void calculate_operation(stack_double **number_stack, char *operation);
void calculate_function(stack_double **number_stack, char *operation);

#endif  // SMART_CALC_H
