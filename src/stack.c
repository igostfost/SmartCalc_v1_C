#include "stack.h"

/// @brief Инициализация первого элемента стэка
/// @return указатель на элемент стэка
StackNode *init() {
  StackNode *root = NULL;
  while (root == NULL) {
    root = (StackNode *)malloc(sizeof(StackNode));
  }
  root->next_node = NULL;
  return root;
}

/// @brief Создаем новый верхний элемент стэка
/// @param root указатель на старый верхний элемент стэка
/// @return указатель на новый верхний элемент стэка
StackNode *push(StackNode *root) {
  StackNode *top = NULL;
  while (top == NULL) {
    top = (StackNode *)malloc(sizeof(StackNode));
  }
  top->next_node = root;

  return top;
}

/// @brief Удаляет верхний элемент стэка
/// @param root указатель на верхний элемент стэка
/// @return указатель на следующий элемент
StackNode *pop(StackNode *root) {
  StackNode *top = root->next_node;
  free(root);
  return top;
}

/// @brief Копирует стэк
void copy_stack(StackNode *source, StackNode **result) {
  StackNode *tmp_result = init();
  *result = tmp_result;
  copy_node(source, tmp_result);
  while (source->next_node != NULL) {
    StackNode *tmp = init();
    tmp_result->next_node = tmp;
    tmp_result = tmp_result->next_node;
    source = source->next_node;
    copy_node(source, tmp_result);
  }
  tmp_result->next_node = NULL;
}

void copy_node(StackNode *source, StackNode *result) {
  if (source != NULL && result != NULL) {
    result->priority = source->priority;
    if (source->priority == -1) {
      result->node_data.d_number = source->node_data.d_number;
    } else {
      result->node_data.d_symbol = source->node_data.d_symbol;
    }
  }
}

/// @brief Удаляем стэк
void delete_stack(StackNode *root) {
  StackNode *tmp = NULL;
  while (root != NULL) {
    tmp = root->next_node;
    free(root);
    root = tmp;
  }
}
