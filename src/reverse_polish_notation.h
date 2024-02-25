#ifndef REVERSE_POLISH_NOTATION_H
#define REVERSE_POLISH_NOTATION_H

#include "stack.h"

lexem *reverse_polish_notation(char *input_array, int *number_lexem);
lexem *lexem_array(char *input_string, int *number_lexem);
double get_value(char **pointer);
void oper_name(char **pointer, char *name_operator);
int oper_status(char symbol);
lexem *get_rpn_array(lexem *lexem_arr, int *number_lexem);
stack *process_right_bracket(lexem *rpn_array, stack *stack_oper, int *count);
stack *low_priority_oper(const lexem current_lexem, lexem *rpn_array,
                         stack *stack_oper, int *count);
void oper_clean(lexem *rpn_array, stack *stack_oper, int *count);
int error_lexem_arr(lexem *lexem_arr, const int number_lexem);
#endif  // REVERSE_POLISH_NOTATION_H