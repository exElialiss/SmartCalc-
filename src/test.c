#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char *items;
    int top;
    int capacity;
} Stack;

void initStack(Stack *stack, int capacity) {
    stack->items = (char *)malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int push(Stack *stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return 0; // Error
    }
    stack->items[++stack->top] = item;
    return 1; // Success
}

char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1; // Error
    }
    return stack->items[stack->top--];
}

char peek(Stack *stack) {
    if (isEmpty(stack)) {
        return -1; // Error
    }
    return stack->items[stack->top];
}

void freeStack(Stack *stack) {
    free(stack->items);
    stack->top = -1;
    stack->capacity = 0;
}

int isOperator(char symbol) {
  return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int precedence(char symbol) {
  switch (symbol) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return 0;
  }
}

void infixToPostfix(char *infix, char *postfix) {
  Stack stack;
  initStack(&stack);
  int i = 0, j = 0;

  while (infix[i] != '\0') {
    char symbol = infix[i];

    if (isalnum(symbol)) {
      postfix[j++] = symbol;
    } else if (symbol == '(') {
      push(&stack, symbol);
    } else if (symbol == ')') {
      while (!isEmpty(&stack) && peek(&stack) != '(') {
        postfix[j++] = pop(&stack);
      }
      pop(&stack); // Remove '(' from stack
    } else if (isOperator(symbol)) {
      while (!isEmpty(&stack) &&
             precedence(peek(&stack)) >= precedence(symbol)) {
        postfix[j++] = pop(&stack);
      }
      push(&stack, symbol);
    }
    i++;
  }

  while (!isEmpty(&stack)) {
    postfix[j++] = pop(&stack);
  }

  postfix[j] = '\0';
}

int evaluatePostfix(char *postfix) {
    Stack s;
    s.top = -1;
    int i, a, b;

    for (i = 0; postfix[i]; ++i) {
        // Если символ - число, добавляем его в стек
        if (isdigit(postfix[i])) {
            push(&s, postfix[i] - '0');
        } else {
            // Иначе выполняем операцию и добавляем результат обратно в стек
            b = pop(&s);
            a = pop(&s);

            switch (postfix[i]) {
                case '+': push(&s, a + b); break;
                case '-': push(&s, a - b); break;
                case '*': push(&s, a * b); break;
                case '/': push(&s, a / b); break;
            }
        }
    }

    // Возвращаем результат, который должен остаться в стеке
    return pop(&s);
}

int main() {
  char infix[MAX_SIZE];
  char postfix[MAX_SIZE];

  printf("Enter infix expression: ");
  fgets(infix, MAX_SIZE, stdin);

  // Удаляем символ новой строки, если он есть
  size_t ln = strlen(infix) - 1;
  if (infix[ln] == '\n')
    infix[ln] = '\0';

  infixToPostfix(infix, postfix);

  printf("Result: %d\n", evaluatePostfix(postfix));

  return 0;
}