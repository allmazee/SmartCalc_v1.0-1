#include "smart_calc.h"

void push_double(stack_double **head, double value) {
  stack_double *tmp = (stack_double *)malloc(sizeof(stack_double));
  if (tmp == NULL) {
    printf("%s\n", "Error: Out of stack memory");
  } else {
    tmp->value = value;
    tmp->next = *head;
    *head = tmp;
  }
}

double pop_double(stack_double **head) {
  stack_double *tmp;
  double value = 0;
  if (*head == NULL) {
    printf("%s\n", "Error: Stack is empty");
  } else {
    tmp = *head;
    *head = (*head)->next;
    value = tmp->value;
    free(tmp);
  }
  return value;
}

void clear_double(stack_double **head) {
  while (*head) {
    pop_double(head);
  }
}

void push_str(stack_str **head, char *value, int priority) {
  stack_str *tmp = (stack_str *)malloc(sizeof(stack_str));
  if (tmp == NULL) {
    printf("%s\n", "Error: Out of stack memory");
  } else {
    strcpy(tmp->value, value);
    tmp->priority = priority;
    tmp->next = *head;
    *head = tmp;
  }
}

void pop_str(stack_str **head, char *buff) {
  stack_str *tmp;
  if (*head == NULL) {
    printf("%s\n", "Error: Stack is empty");
  } else {
    tmp = *head;
    *head = (*head)->next;
    strcpy(buff, tmp->value);
    free(tmp);
  }
}

char *peek_str(stack_str *head) {
  if (head == NULL) {
    printf("%s\n", "Error: Stack is empty");
  }
  return head->value;
}

void clear_str(stack_str **head) {
  while (*head) {
    stack_str *tmp = *head;
    *head = (*head)->next;
    free(tmp);
  }
}
