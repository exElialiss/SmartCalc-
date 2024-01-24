#include "validation.h"

int input_array_validation(char *input_array) {
  int output = OK;
  if (input_array == NULL) {
    output = MEMORY_ERROR;
  } else {
    if (output == OK) {
      output = check_amount_brackets(input_array);
    }
    // Проверка названий операторов
    if (output == OK) {
      output = check_name_operators(input_array);
    }
    // Проверка точек в числах
    if (output == OK) {
      output = check_points(input_array);
    }
  }
  return output;
}

int check_amount_brackets(char *input_array) {
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
        char *potential_operator = init_char_array(size + 1);
        if (potential_operator == NULL) {
          output = MEMORY_ERROR;
        } else {
          potential_operator = strncpy(potential_operator, start, size);
          output = compare_name_operator(potential_operator);
          free(potential_operator);
          potential_operator = NULL;
          start = NULL;
          end = NULL;
        }
      }
    }
  }
  return output;
}

int compare_name_operator(const char *potential_operator) {
  int output = OK;
  if (potential_operator == NULL) {
    output = MEMORY_ERROR;
  } else {
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
      output = find_point(&input_array[i], &start, &point, &end);
      if (output == OK) {
        output = check_pointers(&input_array[i], &start, &point, &end);
      }
      if (output == SYNTAX_ERROR) {
        start = NULL;
        end = NULL;
        point = NULL;
      }
    }
  }
  return output;
}

int find_point(char *symbol, char **start, char **point, char **end) {
  int output = OK;
  if (isdigit(*symbol) && *start == NULL) {
    *start = symbol;
  } else if (isdigit(*symbol) && *start != NULL) {
    *end = symbol;
  } else if (*symbol == '.' && *point == NULL) {
    *point = symbol;
  } else if (*symbol == '.' && *point != NULL) {
    output = SYNTAX_ERROR;
    *start = NULL;
    *end = NULL;
    *point = NULL;
  }
  return output;
}

int check_pointers(char *symbol, char **start, char **point, char **end) {
  int output = OK;
  if ((!(isdigit(*symbol)) && *symbol != '.') ||
      ((isdigit(*symbol) || *symbol == '.') && *(symbol + 1) == '\0')) {
    if (*point != NULL && *start != NULL && *end != NULL) {
      if (*point - *start > 0 && *end - *point > 0) {
        *start = NULL;
        *end = NULL;
        *point = NULL;
      } else {
        output = SYNTAX_ERROR;
      }
    } else if (*point != NULL && (*start == NULL || *end == NULL)) {
      output = SYNTAX_ERROR;
    } else if (*point == NULL) {
      *start = NULL;
      *end = NULL;
    }
  }
  return output;
}

char *init_char_array(const int length) {
  return (char *)calloc(length, sizeof(char));
}