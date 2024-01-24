#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

double stack[MAX_SIZE];
int top = -1;

void push(double value) {
  if (top < MAX_SIZE - 1) {
    stack[++top] = value;
  } else {
    printf("Стек переполнен\n");
    exit(EXIT_FAILURE);
  }
}

double pop() {
  if (top >= 0) {
    return stack[top--];
  } else {
    printf("Стек пуст\n");
    exit(EXIT_FAILURE);
  }
}

int isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
         ch == 'c' || ch == 's' || ch == 't' || ch == 'g' || ch == 'q' ||
         ch == 'v' || ch == 'a' || ch == 'i' || ch == 'n';
}

int isOperand(char ch) { return isdigit(ch) || ch == '.'; }

double evaluateRPN(char *expression) {
  for (int i = 0; expression[i] != '\0'; i++) {
    if (isOperand(expression[i])) {
      push(strtod(&expression[i], NULL));
      while (isOperand(expression[i + 1]) || expression[i + 1] == '.') {
        i++;
      }
    } else if (isOperator(expression[i])) {
      double operand2, operand1;
      switch (expression[i]) {
      case '+':
        push(pop() + pop());
        break;
      case '-':
        operand2 = pop();
        operand1 = pop();
        push(operand1 - operand2);
        break;
      case '*':
        push(pop() * pop());
        break;
      case '/':
        operand2 = pop();
        operand1 = pop();
        if (operand2 != 0) {
          push(operand1 / operand2);
        } else {
          printf("Ошибка: деление на ноль\n");
          exit(EXIT_FAILURE);
        }
        break;
      case '^':
        operand2 = pop();
        operand1 = pop();
        push(pow(operand1, operand2));
        break;
      case 'c':
        push(cos(pop()));
        break;
      case 's':
        push(sin(pop()));
        break;
      case 't':
        push(tan(pop()));
        break;
      case 'g':
        push(1.0 / tan(pop()));
        break;
      case 'q':
        push(1.0 / cos(pop()));
        break;
      case 'v':
        push(1.0 / sin(pop()));
        break;
      case 'a':
        if (expression[i + 1] == 'c') {
          push(acos(pop()));
        } else if (expression[i + 1] == 's') {
          push(asin(pop()));
        } else if (expression[i + 1] == 't') {
          push(atan(pop()));
        } else {
          printf("Ошибка: неизвестная функция\n");
          exit(EXIT_FAILURE);
        }
        break;
      }
    }
  }

  // Результат будет на вершине стека после вычисления всего выражения
  return pop();
}

int main() {
  char expression[] = "1+1";
  double result = evaluateRPN(expression);
  printf("Результат вычислений: %lf\n", result);

  return 0;
}
