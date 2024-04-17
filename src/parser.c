#include "smart_calc.h"

int parser(char *str, char **tokens) {
  if (str == NULL) return OUT_OF_TOKENS;
  char buff[STACK_MAX_SIZE];
  int count = 0;
  int length = strlen(str);
  if (nan_finder(str) == NAN_OPERAND) return NAN_OPERAND;
  for (int i = 0; i < length;) {
    memset(buff, 0, STACK_MAX_SIZE);
    if (count >= STACK_MAX_SIZE) return OUT_OF_TOKENS;
    if (isdigit(str[i])) {
      int k = 0;
      while (!is_operation(str[i]) && i < length && str[i] != ')' &&
             str[i] != 'm') {
        buff[k++] = str[i++];
      }
    } else if (is_operation(str[i]) || str[i] == '(' || str[i] == ')' ||
               str[i] == 'x') {
      buff[0] = str[i++];
    } else if (is_function(str[i])) {
      int k = 0;
      while (str[i] != '(') {
        buff[k++] = str[i++];
      }
    } else if (str[i] == 'm') {
      strcpy(buff, "mod");
      i += 3;
    }
    strcpy(tokens[count], buff);
    count++;
  }
  return count;
}

int nan_finder(char *str) {
  char *validated_symbols = "1234567890x()+-*/^sincosatanmdqrlg.";
  int open_braces = 0, close_braces = 0, status = 0;
  int length = strlen(str);
  for (int i = 0; i < length && !status; i++) {
    if (strchr(validated_symbols, str[i])) {
      if (str[i] == '(' || str[i] == ')') {
        str[i] == '(' ? open_braces++ : close_braces++;
      } else if (isdigit(str[i]) || str[i] == 'x') {
        status = nan_digit(str, &i);
        if (str[i] == ')') close_braces++;
      } else if (is_function(str[i])) {
        status = nan_function(str, &i);
      } else if (is_operation(str[i])) {
        if (!i && str[i] != '+' && str[i] != '-')
          status = NAN_OPERAND;
        else if (str[i] != '+' && str[i] != '-' && !isdigit(str[i - 1]) &&
                 str[i - 1] != ')') {
          status = NAN_OPERAND;
        }
      }
    } else {
      status = NAN_OPERAND;
    }
  }
  if (open_braces != close_braces) status = NAN_OPERAND;
  return status;
}

int nan_digit(char *str, int *i) {
  int status = 0;
  int is_dot = 0;
  *i += 1;
  int operation = 1;
  int length = strlen(str);
  while (*i < length && !status && operation && str[*i] != ')') {
    operation = !is_operation(str[*i]);
    if (str[*i] == 'm') {
      if ((*i + 2) >= length || !(str[*i + 1] == 'o' && str[*i + 2] == 'd'))
        return NAN_OPERAND;
     *i += 2;
      operation = 0;
    } else if ((str[*i] == '.' && is_dot) ||
               (operation && !isdigit(str[*i]) && str[*i] != '.')) {
      return NAN_OPERAND;
    } else if (operation) {
      if (str[*i] == '.') is_dot = 1;
      *i += 1;
    }
  }
  return status;
}

int nan_function(char *str, int *i) {
  int status = 0;
  if (str[*i] == 'c' || (str[*i] == 's' && str[*i + 1] != 'q') ||
      str[*i] == 't') {
    status = nan_trigonometric(str, i);
  } else if (str[*i] == 'a') {
    *i += 1;
    status = nan_trigonometric(str, i);
  } else if (str[*i] == 's') {
    if (str[*i + 1] != 'q' && str[*i + 2] != 'r' && str[*i + 3] != 't') {
      status = NAN_OPERAND;
    }
    *i += 3;
  } else if (str[*i] == 'l') {
    if (str[*i + 1] == 'n') {
      *i += 1;
    } else if (str[*i + 1] == 'o' && str[*i + 2] == 'g') {
      *i += 2;
    } else {
      status = NAN_OPERAND;
    }
  }
  if (!status && str[*i + 1] != '(') {
    status = NAN_OPERAND;
  }
  return status;
}

int nan_trigonometric(char *str, int *i) {
  int status = 0;
  if (str[*i] == 'c') {
    if (str[*i + 1] != 'o' || str[*i + 2] != 's') {
      status = NAN_OPERAND;
    }
  } else if (str[*i] == 's') {
    if (str[*i + 1] != 'i' || str[*i + 2] != 'n') {
      status = NAN_OPERAND;
    }
  } else if (str[*i] == 't') {
    if (str[*i + 1] != 'a' || str[*i + 2] != 'n') {
      status = NAN_OPERAND;
    }
  }
  *i += 2;
  return status;
}
