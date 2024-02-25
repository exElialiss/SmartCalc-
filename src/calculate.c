#include "calculate.h"

int calculate(lexem *rpn_array, const int number_lexem, double *res,
              double x_val) {
  int output = OK;
  if (rpn_array == NULL || res == NULL) {
    output = MEMORY_ERROR;
  } else {
    *res = 0.0;
    stack *stack_value = init_stack();
    if (rpn_array != NULL) {
      for (int i = 0; i < number_lexem; ++i) {
        if (rpn_array[i].status == x_status) {
          rpn_array[i].value = x_val;
          rpn_array[i].status = number;
        }
      }
    }
    for (int i = 0; i < number_lexem && stack_value != NULL; ++i) {
      if (rpn_array[i].status == number) {
        stack_value = push(stack_value, rpn_array[i]);
      } else if (rpn_array[i].status == function) {
        stack_value = calc_func(rpn_array[i], stack_value);
      } else if (rpn_array[i].status == operator_status) {
        stack_value = calc_oper(rpn_array[i], stack_value);
      }
    }
    if (stack_value != NULL && stack_value->size == 1) {
      *res = stack_value->current_lexem.value;
      free_stack(stack_value);
    } else if (stack_value != NULL && stack_value->size != 1) {
      output = SYNTAX_ERROR;
      free_stack(stack_value);
    } else {
      output = SYNTAX_ERROR;
    }
  }
  return output;
}

stack *calc_oper(const lexem current_lexem, stack *stack_value) {
  if (stack_value != NULL) {
    if (stack_value->size != 0) {
      if (current_lexem.priority == u_sub_pr && current_lexem.name[0] == '-') {
        stack_value->current_lexem.value *= -1;
      } else if (current_lexem.priority != u_sub_pr && stack_value->size >= 2) {
        double value_2 = stack_value->current_lexem.value;
        pop(&stack_value);
        double value_1 = stack_value->current_lexem.value;
        pop(&stack_value);
        double result = 0.0;
        if (strcmp(current_lexem.name, "+") == 0) {
          result = value_1 + value_2;
        } else if (strcmp(current_lexem.name, "-") == 0) {
          result = value_1 - value_2;
        } else if (strcmp(current_lexem.name, "*") == 0) {
          result = value_1 * value_2;
        } else if (strcmp(current_lexem.name, "/") == 0) {
          result = value_1 / value_2;
        } else if (strcmp(current_lexem.name, "^") == 0) {
          result = pow(value_1, value_2);
        } else if (strcmp(current_lexem.name, "m") == 0) {
          result = fmod(value_1, value_2);
        }
        lexem *new_lexem = (lexem *)calloc(1, sizeof(lexem));
        init_lexem(new_lexem, number, result, "\0");
        stack_value = push(stack_value, *new_lexem);
        free(new_lexem);
        new_lexem = NULL;
      } else if (current_lexem.priority != u_sum_pr) {
        free_stack(stack_value);
        stack_value = NULL;
      }
    }
  } else {
    free_stack(stack_value);
    stack_value = NULL;
  }
  return stack_value;
}

stack *calc_func(const lexem current_lexem, stack *stack_value) {
  double result = 0.0;
  const char *name_function = current_lexem.name;
  double value = stack_value->current_lexem.value;
  if (name_function != NULL) {
    if (strcmp(name_function, "c") == 0) {
      result = cos(value);
    } else if (strcmp(name_function, "t") == 0) {
      result = tan(value);
    } else if (strcmp(name_function, "si") == 0) {
      result = sin(value);
    } else if (strcmp(name_function, "sq") == 0) {
      result = sqrt(value);
    } else if (strcmp(name_function, "ln") == 0) {
      result = log(value);
    } else if (strcmp(name_function, "lg") == 0) {
      result = log10(value);
    } else if (strcmp(name_function, "ac") == 0) {
      result = acos(value);
    } else if (strcmp(name_function, "as") == 0) {
      result = asin(value);
    } else if (strcmp(name_function, "at") == 0) {
      result = atan(value);
    }
  }
  if (stack_value != NULL) {
    if (stack_value->size != 0) {
      pop(&stack_value);
      lexem *new_lexem = (lexem *)calloc(1, sizeof(lexem));
      init_lexem(new_lexem, number, result, "\0");
      stack_value = push(stack_value, *new_lexem);
      free(new_lexem);
      new_lexem = NULL;
    } else {
      free_stack(stack_value);
      stack_value = NULL;
    }
  }
  return stack_value;
}

void annutiet_calc(double loan_amount, const int loan_term,
                   double interest_rate, double *pay_month, double *overpay,
                   double *result_sum) {
  interest_rate /= 12;
  double monthly_interest_rate = pow(1 + interest_rate, loan_term);
  double annuity_coefficient =
      (interest_rate * monthly_interest_rate) / (monthly_interest_rate - 1);

  *pay_month = loan_amount * annuity_coefficient;
  *result_sum = *pay_month * loan_term;
  *overpay = *result_sum - loan_amount;
}
