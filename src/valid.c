#include "valid.h"

#include "stack.h"

int validation_array(char *input_array) {
  int output = OK;
  if (input_array == NULL) {
    output = MEMORY_ERROR;
  } else {
    if (output == OK) {
      output = check_brackets(input_array);
    }
    if (output == OK) {
      output = check_name_operators(input_array);
    }
    if (output == OK) {
      output = check_points(input_array);
    }
    if (output == OK) {
      output = check_oper_place(input_array);
    }
  }
  return output;
}

int check_oper_place(char *input_array) {
  int output = OK;
  char operators[] = {'*', '/', '+', '-', '^'};
  int len = strlen(input_array);

  if (input_array[len - 1] == '+' || input_array[len - 1] == '-' ||
      input_array[len - 1] == '*' || input_array[len - 1] == '/' ||
      input_array[len - 1] == '^') {
    output = SYNTAX_ERROR;
  }

  for (int i = 0; i < len - 1; i++) {
    int is_operator = 0;
    int operator_count = 0;
    int operators_count = sizeof(operators) / sizeof(operators[0]);
    for (int j = 0; j < operators_count; j++) {
      if (input_array[i] == operators[j]) {
        is_operator = 1;
        operator_count++;
        break;
      }
    }
    if (is_operator) {
      int is_next_operator = 0;
      for (int j = 0; j < operators_count; j++) {
        if (input_array[i + 1] == operators[j]) {
          is_next_operator = 1;
          break;
        }
      }
      if (is_next_operator) {
        output = SYNTAX_ERROR;
        break;
      }
    }
  }
  return output;
}

int check_brackets(char *input_array) {
  int output = OK;
  if (input_array == NULL) {
    output = MEMORY_ERROR;
  } else {
    size_t length = strlen(input_array);
    int count_brackets = 0;
    for (size_t i = 0; i < length && count_brackets >= 0; i++) {
      if (input_array[i] == '(') {
        count_brackets++;
      } else if (input_array[i] == ')') {
        count_brackets--;
      }
    }
    if (count_brackets != 0) {
      output = SYNTAX_ERROR;
    }
  }
  return output;
}

int check_name_operators(char *input_array) {
  int output = OK;
  if (input_array == NULL) {
    output = MEMORY_ERROR;
  } else {
    size_t length = strlen(input_array);
    char *start = NULL;
    char *end = NULL;

    for (size_t i = 0; i < length && output == OK; i++) {
      if (isalpha(input_array[i]) && start == NULL) {
        start = &input_array[i];
        end = &input_array[i];
      } else if (isalpha(input_array[i]) && start != NULL) {
        end = &input_array[i];
      }

      if ((!(isalpha(input_array[i])) || input_array[i + 1] == '\0') &&
          start != NULL) {
        size_t size = end - start + 1;
        if (start[0] == 'a' || start[0] == 'c' || start[0] == 's' ||
            start[0] == 't' || start[0] == 'l') {
          size += 1;
        }
        char *potential_operator = (char *)calloc(size + 1, sizeof(char));
        if (potential_operator == NULL) {
          output = MEMORY_ERROR;
        } else {
          potential_operator = strncpy(potential_operator, start, size);
          int match = 1;
          if (strcmp(potential_operator, "mod") == 0 ||
              strcmp(potential_operator, "cos(") == 0 ||
              strcmp(potential_operator, "sin(") == 0 ||
              strcmp(potential_operator, "tan(") == 0 ||
              strcmp(potential_operator, "acos(") == 0 ||
              strcmp(potential_operator, "asin(") == 0 ||
              strcmp(potential_operator, "atan(") == 0 ||
              strcmp(potential_operator, "sqrt(") == 0 ||
              strcmp(potential_operator, "ln(") == 0 ||
              strcmp(potential_operator, "log(") == 0 ||
              strcmp(potential_operator, "x") == 0) {
            match = 0;
          }
          if (match) {
            output = SYNTAX_ERROR;
          }
          free(potential_operator);
          start = NULL;
          end = NULL;
        }
      }
    }
  }
  return output;
}

int check_points(char *input_array) {
  int output = OK;
  if (input_array == NULL) {
    output = MEMORY_ERROR;
  } else {
    size_t length = strlen(input_array);
    char *start = NULL;
    char *end = NULL;
    char *point = NULL;
    for (size_t i = 0; i < length && output == OK; i++) {
      char *symbol = &input_array[i];
      if (isdigit(*symbol) && start == NULL) {
        start = symbol;
      } else if (isdigit(*symbol) && start != NULL) {
        end = symbol;
      } else if (*symbol == '.' && point == NULL) {
        point = symbol;
      } else if (*symbol == '.' && point != NULL) {
        output = SYNTAX_ERROR;
        start = NULL;
        end = NULL;
        point = NULL;
      }
      if (output == OK) {
        if ((!isdigit(*symbol) && *symbol != '.') ||
            ((isdigit(*symbol) || *symbol == '.') && *(symbol + 1) == '\0')) {
          if (point != NULL && start != NULL && end != NULL) {
            if (point - start > 0 && end - point > 0) {
              start = NULL;
              end = NULL;
              point = NULL;
            } else {
              output = SYNTAX_ERROR;
            }
          } else if (point != NULL && (start == NULL || end == NULL)) {
            output = SYNTAX_ERROR;
          } else if (point == NULL) {
            start = NULL;
            end = NULL;
          }
        }
      }
    }
  }
  return output;
}
