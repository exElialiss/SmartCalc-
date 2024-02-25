#ifndef CALCULATE_H
#define CALCULATE_H

#include "stack.h"

int calculate(lexem *rpn_array, const int number_lexem, double *res,
              double x_val);
stack *calc_oper(const lexem lexem_, stack *stack_value);
stack *calc_func(const lexem current_lexem, stack *stack_value);
void annutiet_calc(double loan_amount, const int loan_term,
                   double interest_rate, double *pay_month, double *overpay,
                   double *result_sum);

#endif  // CALCULATE_H