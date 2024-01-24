#include "validation.h"

void initStack(Stack *stack, int capacity) {
  stack->array = (char *)malloc(capacity * sizeof(char));
  stack->size = 0;
  stack->capacity = capacity;
}

void freeStack(Stack *stack) {
  free(stack->array);
  stack->size = 0;
  stack->capacity = 0;
}

void push(Stack *stack, char value) {
  if (stack->size == stack->capacity) {
    // Если стек полон, увеличиваем его размер
    stack->capacity *= 2;
    stack->array =
        (char *)realloc(stack->array, stack->capacity * sizeof(char));
  }

  stack->array[stack->size++] = value;
}

char pop(Stack *stack) { return stack->array[--stack->size]; }

char top(const Stack *stack) { return stack->array[stack->size - 1]; }

int isEmpty(const Stack *stack) { return stack->size == 0; }

double calculate(const char *expression) {
  char op = '+';
  double result = 0.0;
  int i = 0;

  while (expression[i] != '\0') {
    if (isdigit(expression[i]) || (expression[i] == '-' && i == 0)) {
      // Читаем число из строки
      char *endptr;
      double operand = strtod(&expression[i], &endptr);
      result = (op == '+' ? result + operand : result - operand);
      i = endptr - expression;
    } else if (expression[i] == '+') {
      op = '+';
      i++;
    } else if (expression[i] == '-') {
      op = '-';
      i++;
    } else if (expression[i] == '*') {
      i++;
      if (isdigit(expression[i]) ||
          (expression[i] == '-' && isdigit(expression[i + 1]))) {
        char *endptr;
        double operand = strtod(&expression[i], &endptr);
        result *= operand;
        i = endptr - expression;
      }
    } else if (expression[i] == '/') {
      i++;
      if (isdigit(expression[i]) ||
          (expression[i] == '-' && isdigit(expression[i + 1]))) {
        char *endptr;
        double operand = strtod(&expression[i], &endptr);
        if (operand != 0.0) {
          result /= operand;
          i = endptr - expression;
        } else {
          // Обработка деления на ноль
          printf("Error: Division by zero\n");
          return 0.0;
        }
      }
    } else {
      // Пропускаем другие символы
      i++;
    }
  }

  return result;
}