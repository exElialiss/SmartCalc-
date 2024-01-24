#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define OK 0
#define MEMORY_ERROR 2
#define SYNTAX_ERROR 1

typedef enum {ZERO, FIRST, SECOND, THIRD, FOURTH} priority;

typedef struct {
    char type;
    int priority;
    double value;
    int type_id;
    bool is_binary;
} s21_node;

typedef struct {
    int last_index;
    s21_node stack_array[STACK_SIZE];
} s21_stack;

typedef enum { OK, ERROR} errors;

typedef struct {
    char* array;
    int size;
    int capacity;
} Stack;

//int input_array_validation(char* input_array);
void initStack(Stack* stack, int capacity);
void push(Stack* stack, char value);
char pop(Stack* stack);
char top(const Stack* stack);
int isEmpty(const Stack* stack);
void freeStack(Stack* stack);
double calculate(const char* expression);
char *init_char_array(const int length);
int input_array_validation(char *input_array);
int check_allowed_characters(char *input_array);
int check_amount_brackets(char *input_array);
int check_name_operators(char *input_array);
int check_points(char *input_array);
int compare_name_operator(const char *potential_operator);
int find_point(char *symbol, char **start, char **point, char **end);
int check_pointers(char *symbol, char **start, char **point, char **end);

#endif // VALIDATION_H