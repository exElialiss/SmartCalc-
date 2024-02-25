#include "stack.h"

/// @brief | Заполняет поля лексемы |
/// @param  lexem - указатель на лексему lexem *
/// @param  status - статус лексемы int
/// @param  value - значение вещественного числа double
/// @param  name - имя оператора(функции) char *
void init_lexem(lexem *current_lexem, int status, double value, char *name) {
  if (current_lexem != NULL) {
    current_lexem->status = status;
    current_lexem->value = value;
    strcpy(current_lexem->name, name);
    current_lexem->priority = get_priority(name[0]);
  }
}

/// @brief | Возвращает приоритет операции |
/// @param  symbol - первый символ оператора(функции)
/// @return приоритет операции int
int get_priority(char operator) {
  int priority = 0;
  if (operator== '+' || operator== '-') {
    priority = sum_pr;
  } else if (operator== '*' || operator== '/') {
    priority = mul_pr;
  } else if (operator== '^') {
    priority = pow_pr;
  } else if (operator== 'm') {
    priority = mod_pr;
  } else if (operator== ')') {
    priority = r_brack_pr;
  } else {
    priority = l_brack_pr;
  }
  return priority;
}

/// @brief | Инициализация стека лексем |
/// @param  lexem- добавляемая лексема
/// @return указатель на верхний элемент
stack *init_stack() {
  stack *head = (stack *)malloc(sizeof(stack));
  if (head != NULL) {
    head->last_lexem = NULL;
    head->size = 0;
  }
  return head;
}

/// @brief | Создание указателя на новый элемент стека |
/// @param  lexem- добавляемая лексема lexem
/// @return указатель на новый элемент
stack *pointer_elem(lexem current_lexem) {
  stack *head = (stack *)malloc(sizeof(stack));
  if (head != NULL) {
    head->current_lexem = current_lexem;
    head->last_lexem = NULL;
    head->size = 0;
  }
  return head;
}

/// @brief | Добавление новой лексемы в стек |
/// @param  head - указатель на верхний элемент
/// @param  lexem - добавляемая лексема
/// @return указатель на верхний элемент
stack *push(stack *head, lexem current_lexem) {
  stack *output = head;
  if (head != NULL && head->size == 0) {
    head->current_lexem = current_lexem;
    ++(head->size);
  } else if (head != NULL && head->size != 0) {
    stack *new_lexem = pointer_elem(current_lexem);
    if (new_lexem != NULL) {
      output = new_lexem;
      new_lexem->last_lexem = head;
      new_lexem->size = head->size + 1;
    }
  }
  return output;
}

/// @brief | Выталкивание верхней лексемы из стека |
/// @param  head - указатель на верхний элемент
/// @return верхняя лексема
lexem pop(stack **head) {
  lexem output = (*head)->current_lexem;
  if ((*head)->size == 1) {
    (*head)->size = 0;
  } else {
    stack *tmp = (*head);
    (*head) = (*head)->last_lexem;
    free(tmp);
  }
  return output;
}

void free_stack(stack *head) {
  if (head != NULL) {
    while (head->last_lexem != NULL) {
      pop(&head);
    }
    free(head);
    head = NULL;
  }
}