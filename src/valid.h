#ifndef VALIDATION_H
#define VALIDATION_H

#include "stack.h"

int validation_array(char *input_array);
int check_oper_place(char *input_array);
int check_brackets(char *input_array);
int check_name_operators(char *input_array);
int check_points(char *input_array);

#endif  // VALIDATION_H