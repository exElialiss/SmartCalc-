#include "reverse_polish_notation.h"

#include "stack.h"

lexem *reverse_polish_notation(char *input_array, int *number_lexem) {
  lexem *rpn_array = NULL;
  if (input_array != NULL && number_lexem != NULL) {
    *number_lexem = 0;
    lexem *lexem_arr = lexem_array(input_array, number_lexem);
    if (lexem_arr != NULL) {
      int result = error_lexem_arr(lexem_arr, *number_lexem);
      if (result == OK) {
        rpn_array = get_rpn_array(lexem_arr, number_lexem);
      }
      free(lexem_arr);
      lexem_arr = NULL;
    }
  }
  return rpn_array;
}

lexem *lexem_array(char *input_string, int *number_lexem) {
  lexem *lexem_arr = NULL;
  if (input_string != NULL && number_lexem != NULL) {
    *number_lexem = 0;
    char *pointer = input_string;
    double value = 0.0;
    int size_lexem_arr = 5;
    lexem_arr = (lexem *)calloc(size_lexem_arr, sizeof(lexem));
    char *name_operator = (char *)calloc(3, sizeof(char));
    int status = -1;
    while (*pointer != '\0') {
      if (*number_lexem == size_lexem_arr - 1) {
        size_lexem_arr *= 2;
        lexem_arr = (lexem *)realloc(lexem_arr, size_lexem_arr * sizeof(lexem));
      }
      if (isdigit(*pointer)) {
        value = get_value(&pointer);
        init_lexem(&lexem_arr[*number_lexem], number, value, name_operator);
        ++(*number_lexem);
      } else if (isalpha(*pointer)) {
        oper_name(&pointer, name_operator);
        status = oper_status(name_operator[0]);
        init_lexem(&lexem_arr[*number_lexem], status, value, name_operator);
        ++(*number_lexem);
      } else {
        name_operator[0] = *pointer;
        ++pointer;
        init_lexem(&lexem_arr[*number_lexem], operator_status, value,
                   name_operator);
        ++(*number_lexem);
      }
      value = 0.0;
      status = -1;
      memset(name_operator, '\0', 3);
    }
    if (!(*number_lexem)) {
      free(lexem_arr);
      lexem_arr = NULL;
    }
    free(name_operator);
    name_operator = NULL;
  }
  return lexem_arr;
}

double get_value(char **pointer) {
  if (!pointer || !(*pointer)) return 0.0;
  const char *start = *pointer;
  while (**pointer && !isdigit(**pointer) && **pointer != '.') {
    ++(*pointer);
    start = *pointer;
  }
  if (!**pointer) return 0.0;
  while (**pointer && (isdigit(**pointer) || **pointer == '.')) ++(*pointer);
  size_t length = *pointer - start;
  char *number = (char *)calloc(length + 1, sizeof(char));
  if (!number) return 0.0;
  strncpy(number, start, length);
  setlocale(LC_NUMERIC, "C");
  double value = strtod(number, NULL);
  free(number);
  return value;
}

void oper_name(char **pointer, char *name_operator) {
  if (pointer == NULL || name_operator == NULL || *pointer == NULL) return;

  switch (**pointer) {
    case 'm':
    case 'c':
    case 't':
      name_operator[0] = **pointer;
      *pointer += 3;
      break;
    case 's':
      strncpy(name_operator, *pointer, 2);
      ++(*pointer);
      if (**pointer == 'i')
        *pointer += 2;
      else
        *pointer += 3;
      break;
    case 'a':
      strncpy(name_operator, *pointer, 2);
      *pointer += 4;
      break;
    case 'l':
      name_operator[0] = **pointer;
      ++(*pointer);
      if (**pointer == 'n') {
        name_operator[1] = **pointer;
        ++(*pointer);
      } else {
        name_operator[1] = 'g';
        *pointer += 2;
      }
      break;
    default:
      name_operator[0] = **pointer;
      ++(*pointer);
      break;
  }
}

int oper_status(char symbol) {
  int status = -1;
  switch (symbol) {
    case 'x':
      status = x_status;
      break;
    case 'm':
      status = operator_status;
      break;
    default:
      status = function;
      break;
  }
  return status;
}

lexem *get_rpn_array(lexem *lexem_arr, int *number_lexem) {
  lexem *rpn_array = NULL;
  if (lexem_arr != NULL) {
    rpn_array = (lexem *)calloc(*number_lexem, sizeof(lexem));
    stack *stack_oper = init_stack();
    int count = 0;
    for (int i = 0; i < *number_lexem; ++i) {
      if (lexem_arr[i].status == number || lexem_arr[i].status == x_status) {
        rpn_array[count++] = lexem_arr[i];
      } else if (lexem_arr[i].status == function) {
        stack_oper = push(stack_oper, lexem_arr[i]);
      } else {
        if (lexem_arr[i].priority == r_brack_pr) {
          stack_oper = process_right_bracket(rpn_array, stack_oper, &count);
          if (stack_oper == NULL) {
            break;
          }
        } else if (lexem_arr[i].priority == l_brack_pr ||
                   stack_oper->size == 0 ||
                   lexem_arr[i].priority > stack_oper->current_lexem.priority) {
          stack_oper = push(stack_oper, lexem_arr[i]);
        } else if (lexem_arr[i].priority <=
                   stack_oper->current_lexem.priority) {
          stack_oper =
              low_priority_oper(lexem_arr[i], rpn_array, stack_oper, &count);
        }
      }
    }
    oper_clean(rpn_array, stack_oper, &count);
    *number_lexem = count;
  }
  return rpn_array;
}

stack *process_right_bracket(lexem *rpn_array, stack *stack_oper, int *count) {
  if (rpn_array != NULL && stack_oper != NULL && count != NULL) {
    while (stack_oper->size != 0 &&
           stack_oper->current_lexem.priority != l_brack_pr) {
      rpn_array[(*count)++] = pop(&stack_oper);
    }
    if (stack_oper->current_lexem.priority == l_brack_pr) {
      pop(&stack_oper);
    } else {
      free_stack(stack_oper);
      free(rpn_array);
      rpn_array = NULL;
      *count = 0;
    }
    if (stack_oper->current_lexem.status == function) {
      rpn_array[(*count)++] = pop(&stack_oper);
    }
  }
  return stack_oper;
}

stack *low_priority_oper(const lexem current_lexem, lexem *rpn_array,
                         stack *stack_oper, int *count) {
  if (rpn_array != NULL && stack_oper != NULL && count != NULL) {
    while (stack_oper->size != 0 &&
           current_lexem.priority <= stack_oper->current_lexem.priority) {
      rpn_array[(*count)++] = pop(&stack_oper);
    }
    stack_oper = push(stack_oper, current_lexem);
  }
  return stack_oper;
}

void oper_clean(lexem *rpn_array, stack *stack_oper, int *count) {
  if (rpn_array != NULL && stack_oper != NULL && count != NULL) {
    while (stack_oper->size != 0) {
      rpn_array[(*count)++] = pop(&stack_oper);
    }
    free_stack(stack_oper);
  }
}

int error_lexem_arr(lexem *lexem_arr, const int number_lexem) {
  int output = OK;
  if (lexem_arr == NULL) {
    output = MEMORY_ERROR;
  } else {
    for (int i = 0; i < number_lexem; ++i) {
      if (lexem_arr[i].status == operator_status &&
          lexem_arr[i].priority == sum_pr) {
        if ((i == 0 || (i != 0 && lexem_arr[i - 1].status == operator_status &&
                        lexem_arr[i - 1].priority == l_brack_pr)) &&
            i != number_lexem - 1 &&
            (lexem_arr[i + 1].status == function ||
             lexem_arr[i + 1].status == number ||
             lexem_arr[i + 1].status == x_status)) {
          if (lexem_arr[i].name[0] == '+') {
            lexem_arr[i].priority = u_sum_pr;
          } else {
            lexem_arr[i].priority = u_sub_pr;
          }
        }
      }
    }
    for (int i = 0; i < number_lexem && output == OK; ++i) {
      if (lexem_arr[i].status == operator_status &&
          lexem_arr[i].priority == l_brack_pr &&
          lexem_arr[i + 1].status == operator_status &&
          lexem_arr[i + 1].priority == r_brack_pr) {
        output = SYNTAX_ERROR;
      }
    }
    for (int i = 0; i < number_lexem && output == OK; ++i) {
      if (lexem_arr[i].status == function && i != 0 &&
          lexem_arr[i - 1].status == operator_status &&
          (lexem_arr[i - 1].priority == r_brack_pr ||
           lexem_arr[i - 1].priority == mod_pr)) {
        output = SYNTAX_ERROR;
      }
    }
  }
  return output;
}
