#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>

#define UO_MINUS '~'
#define UO_PLUS '#'
#define MOD '%'
#define SIN 's'
#define COS 'c'
#define TAN 't'
#define ASIN 'S'
#define ACOS 'C'
#define ATAN 'T'
#define SQRT 'v'
#define LN 'l'
#define LOG 'L'

/// @brief объединение, которое хранит даннные для нашего стека StackNode.
/// Данные: оператор/функция - char, или число - double
typedef union data {
  char d_symbol;
  double d_number;
} data;

/// @brief структура, хранящая type(тип данных и их приоретет),
/// данные и указатель на следующую структуру
typedef struct StackNode {
  /*-1: число;
     0: переменная x;
     1: - и +;
     2: mod, / и *;
     3: ^ правоассоциативная степень;
     4: унарные операторы;
     5: тригонометрические функции;
     6: ( и )
  */
  char priority;
  data node_data;
  struct StackNode *next_node;
} StackNode;

StackNode *init();
StackNode *push(StackNode *root);
StackNode *pop(StackNode *root);
void delete_stack(StackNode *root);
void copy_stack(StackNode *source, StackNode **result);
void copy_node(StackNode *source, StackNode *result);

#endif  // SRC_S21_STACK_H_
