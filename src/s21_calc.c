#include "s21_calc.h"

// int main() {
//   double res = 0.0;
//   double parameter_x = 0;
//   double massive_x[1000];
//   double massive_y[1000];
//   double x_min = 1;
//   double x_max = 1;

//   printf("vvedite zapis':  ");
//   char string[1000];
//   fgets(string, 1000, stdin);
//   printf("%s\n", string);
//   s21_calculate_result(string, &res, parameter_x, massive_x,
//                                 massive_y, x_min, x_max);
//   printf("answer : %f\n", res);
//   return 0;
// }

/// @brief Обрабатывает поданное строковое выражение
/// на ошибки, унарные знаки и переводит в стэк в инфиксной нотации
/// @param string строковое выражение
/// @param stack стэковое представление выражения
/// @return 1 в случае ошибки и 0 в случае успеха
int make_stack_from_string(char *string, StackNode **stack) {
  int error = 0;
  char *tmp_string = NULL;
  error = fix_string(string, &tmp_string);
  if (error == 0) {
    find_unarity(tmp_string);
    error = to_stack(tmp_string, stack);
    if (error == 0) error = check_left_symbol(*stack);
    if (error == 0) {
      reverse_stack(stack);
      error = check_right_symbol(*stack);
    }
    if (error == 0) error = brackets_complects(*stack);
  }
  free(tmp_string);
  return error;
}

/// @brief Удаляет из строки пробелы, переносы строк и табуляцию
int fix_string(char *string, char **result) {
  int error = 0;
  int length = strlen(string);
  while (*result == NULL) *result = (char *)malloc(sizeof(char) * (length + 1));
  for (int i = 0, j = 0; i <= length; i++) {
    if (string[i] != ' ' && string[i] != '\n' && string[i] != '\t') {
      (*result)[j] = string[i];
      j++;
    }
  }
  if (strlen(*result) == 0) {
    error = 1;
  }
  return error;
}

/// @brief находим унарные знаки минус и плюс и меняем на ~ и #
void find_unarity(char *string) {
  int minus_cnt = 0, plus_cnt = 0, repeat_minus = 0, repeat_plus = 0;
  int not_number = 1;
  int lenght = strlen(string);
  for (int i = 0; i < lenght; i++) {
    if ((not_number || minus_cnt || repeat_minus) && string[i] == '-') {
      string[i] = UO_MINUS;
      repeat_minus = 1;
    }
    if ((not_number || plus_cnt || repeat_plus) && string[i] == '+') {
      string[i] = UO_PLUS;
      repeat_plus = 1;
    }
    if (string[i] == '-') {
      minus_cnt = 1;
      plus_cnt = 0;
      repeat_plus = 0;
    } else if (string[i] == '+') {
      plus_cnt = 1;
      minus_cnt = 0;
      repeat_minus = 0;
    } else {
      minus_cnt = 0;
      plus_cnt = 0;
    }
    if ((string[i] < '0' || string[i] > '9') && string[i] != ')' &&
        string[i] != 'x') {
      not_number = 1;
    } else {
      not_number = 0;
    }
  }
}

int to_stack(char *string, StackNode **stack) {
  int error = 0;
  *stack = init();
  int length = strlen(string);
  for (int i = 0; i < length && error == 0; i++) {
    switch (string[i]) {
      case '-':
        have_case_minus(*stack);
        break;
      case '+':
        have_case_plus(*stack);
        break;
      case '/':
        have_case_division(*stack);
        break;
      case '*':
        have_case_multiplication(*stack);
        break;
      case '^':
        have_case_degree(*stack);
        break;
      case '(':
        have_case_left_bracket(*stack);
        break;
      case ')':
        have_case_right_bracket(*stack);
        break;
      case UO_PLUS:
        have_case_plus_uo(*stack);
        break;
      case UO_MINUS:
        have_case_minus_uo(*stack);
        break;
      case 'x':
        have_case_x(*stack);
        break;
      case 'm':
        error = have_case_mod(*stack, string, &i);
        break;
      case 's':
        error = have_case_s(*stack, string, &i);
        break;
      case 'c':
        error = have_case_cos(*stack, string, &i);
        break;
      case 't':
        error = have_case_tan(*stack, string, &i);
        break;
      case 'a':
        error = have_case_a(*stack, string, &i);
        break;
      case 'l':
        error = have_case_l(*stack, string, &i);
        break;
      default:
        if (string[i] >= '0' && string[i] <= '9') {
          error = have_case_number(*stack, string, &i);
        } else {
          error = 1;
        }
        break;
    }
    if (i < length - 1) {
      *stack = push(*stack);
    }
  }

  return error;
}

void have_case_minus(StackNode *stack) {
  stack->priority = 1;
  stack->node_data.d_symbol = '-';
}

void have_case_plus(StackNode *stack) {
  stack->priority = 1;
  stack->node_data.d_symbol = '+';
}

void have_case_division(StackNode *stack) {
  stack->priority = 2;
  stack->node_data.d_symbol = '/';
}

void have_case_multiplication(StackNode *stack) {
  stack->priority = 2;
  stack->node_data.d_symbol = '*';
}
void have_case_degree(StackNode *stack) {
  stack->priority = 3;
  stack->node_data.d_symbol = '^';
}
void have_case_left_bracket(StackNode *stack) {
  stack->priority = 6;
  stack->node_data.d_symbol = '(';
}
void have_case_right_bracket(StackNode *stack) {
  stack->priority = 6;
  stack->node_data.d_symbol = ')';
}
void have_case_plus_uo(StackNode *stack) {
  stack->priority = 4;
  stack->node_data.d_symbol = UO_PLUS;
}
void have_case_minus_uo(StackNode *stack) {
  stack->priority = 4;
  stack->node_data.d_symbol = UO_MINUS;
}
void have_case_x(StackNode *stack) {
  stack->priority = 0;
  stack->node_data.d_symbol = 'x';
}

int have_case_mod(StackNode *stack, char *string, int *i) {
  int error = 0;
  if (strlen(string) - *i < 3) {
    error = 1;
  }
  if (error == 0) {
    if (string[*i + 1] == 'o' && string[*i + 2] == 'd') {
      *i = *i + 2;
      stack->priority = 2;
      stack->node_data.d_symbol = MOD;
    }
  } else {
    error = 1;
  }
  return error;
}

int have_case_s(StackNode *stack, char *string, int *i) {
  int error = 0;
  int lenght = strlen(string);
  if (lenght - *i >= 3 && string[*i + 1] == 'i' && string[*i + 2] == 'n') {
    *i = *i + 2;
    stack->priority = 5;
    stack->node_data.d_symbol = SIN;
  } else if (lenght - *i >= 4 && string[*i + 1] == 'q' &&
             string[*i + 2] == 'r' && string[*i + 3] == 't') {
    *i = *i + 3;
    stack->priority = 5;
    stack->node_data.d_symbol = SQRT;
  } else {
    error = 1;
  }
  return error;
}

int have_case_cos(StackNode *stack, char *string, int *i) {
  int error = 0;
  if (strlen(string) - *i < 3) {
    error = 1;
  }
  if (error == 0) {
    if (string[*i + 1] == 'o' && string[*i + 2] == 's') {
      *i = *i + 2;
      stack->priority = 5;
      stack->node_data.d_symbol = COS;
    }
  } else {
    error = 1;
  }
  return error;
}

int have_case_tan(StackNode *stack, char *string, int *i) {
  int error = 0;
  if (strlen(string) - *i < 3) {
    error = 1;
  }
  if (error == 0) {
    if (string[*i + 1] == 'a' && string[*i + 2] == 'n') {
      *i = *i + 2;
      stack->priority = 5;
      stack->node_data.d_symbol = TAN;
    }
  } else {
    error = 1;
  }
  return error;
}

int have_case_a(StackNode *stack, char *string, int *i) {
  int error = 0;
  int lenght = strlen(string);
  if (lenght - *i < 4) {
    error = 1;
  }
  if (error == 0) {
    if (lenght - *i >= 4 && string[*i + 1] == 'c' && string[*i + 2] == 'o' &&
        string[*i + 3] == 's') {
      *i = *i + 3;
      stack->priority = 5;
      stack->node_data.d_symbol = ACOS;
    } else if (lenght - *i >= 4 && string[*i + 1] == 's' &&
               string[*i + 2] == 'i' && string[*i + 3] == 'n') {
      *i = *i + 3;
      stack->priority = 5;
      stack->node_data.d_symbol = ASIN;
    } else if (lenght - *i >= 4 && string[*i + 1] == 't' &&
               string[*i + 2] == 'a' && string[*i + 3] == 'n') {
      *i = *i + 3;
      stack->priority = 5;
      stack->node_data.d_symbol = ATAN;
    }
  } else {
    error = 1;
  }
  return error;
}

int have_case_l(StackNode *stack, char *string, int *i) {
  int error = 0;
  int lenght = strlen(string);
  if (lenght - *i < 4) {
    error = 1;
  }
  if (error == 0) {
    if (lenght - *i >= 2 && string[*i + 1] == 'n') {
      *i = *i + 1;
      stack->priority = 5;
      stack->node_data.d_symbol = LN;
    } else if (lenght - *i >= 3 && string[*i + 1] == 'o' &&
               string[*i + 2] == 'g') {
      *i = *i + 2;
      stack->priority = 5;
      stack->node_data.d_symbol = LOG;
    }
  } else {
    error = 1;
  }
  return error;
}

int have_case_number(StackNode *stack, char *string, int *i) {
  int error = 0;
  stack->priority = -1;
  stack->node_data.d_number = string[*i] - '0';
  for (int j = 0; j < 9 && strlen(string) - *i >= 2; j++) {
    if (string[*i + 1] >= '0' && string[*i + 1] <= '9') {
      (*i)++;
      stack->node_data.d_number =
          stack->node_data.d_number * 10 + (string[*i] - '0');
    } else {
      break;
    }
  }
  if (strlen(string) - *i >= 3 &&
      (string[*i + 1] == '.' || string[*i + 1] == ',')) {
    (*i)++;
    if (string[*i + 1] >= '0' && string[*i + 1] <= '9') {
      for (int j = 0; j < 7 && strlen(string) - *i >= 2; j++) {
        if (string[*i + 1] >= '0' && string[*i + 1] <= '9') {
          (*i)++;
          stack->node_data.d_number =
              stack->node_data.d_number + (string[*i] - '0') / pow(10, j + 1);
        } else {
          break;
        }
      }
    } else {
      error = 1;
    }
  }
  return error;
}

/// @brief Разварачиваем порядок указателей в стэке
void reverse_stack(StackNode **stack) {
  StackNode *tmp = NULL, *tmp2 = NULL;
  do {
    tmp = (*stack)->next_node;
    (*stack)->next_node = tmp2;
    tmp2 = (*stack);
    if (tmp != NULL) (*stack) = tmp;
  } while (tmp != NULL);
}

/// @brief проверяет наличие переменной x в поданом выражении (стэке)
int check_x(StackNode *stack) {
  int present = 0;
  StackNode *tmp = stack;
  while (tmp != NULL && tmp->priority != 0) {
    tmp = tmp->next_node;
  }
  if (tmp != NULL && tmp->priority == 0) {
    present = 1;
  }
  return present;
}

/// @brief проверяет строку (поданное выражение) на корректность элемента слева
int check_left_symbol(StackNode *stack) {
  int error = 0;
  int priority = stack->priority;
  StackNode *next_in_stack = stack->next_node;
  if (priority > 0 && stack->node_data.d_symbol != ')') {
    error = 1;
  }
  while (next_in_stack != NULL && error == 0) {
    if (priority == -1 || priority == 0 || priority == 4 || priority == 5) {
      if (next_in_stack->priority == 0 || next_in_stack->priority == -1 ||
          next_in_stack->node_data.d_symbol == ')') {
        error = 1;
      }
    } else if (priority == 1 || priority == 2 || priority == 3) {
      if (next_in_stack->priority != 0 && next_in_stack->priority != -1 &&
          next_in_stack->node_data.d_symbol != ')') {
        error = 1;
      }
    }
    priority = next_in_stack->priority;
    next_in_stack = next_in_stack->next_node;
  }
  return error;
}

/// @brief проверяет строку (поданное выражение) на корректность элемента справа

int check_right_symbol(StackNode *stack) {
  int error = 0;
  int priority = stack->priority;
  StackNode *next_in_stack = stack->next_node;
  if ((priority >= 1 && priority <= 3) || stack->node_data.d_symbol == ')')
    error = 1;
  while (next_in_stack != NULL && error == 0) {
    if (priority == -1 || priority == 0) {
      if (next_in_stack->priority == 0 || next_in_stack->priority == -1 ||
          next_in_stack->node_data.d_symbol == '(') {
        error = 1;
      }
    } else if (priority == 1 || priority == 2 || priority == 3 ||
               priority == 4) {
      if ((next_in_stack->priority >= 1 && next_in_stack->priority <= 3) ||
          next_in_stack->node_data.d_symbol == ')') {
        error = 1;
      }
    } else if (priority == 5) {
      if (next_in_stack->priority == -1 ||
          next_in_stack->node_data.d_symbol != '(') {
        error = 1;
      }
    } else {
      if (next_in_stack->node_data.d_symbol == ')') {
        if (stack->node_data.d_symbol == '(') {
          error = 1;
        }
      }
      if (next_in_stack->node_data.d_symbol == '(') {
        if (stack->node_data.d_symbol == ')') {
          error = 1;
        }
      }
    }
    priority = next_in_stack->priority;
    stack = next_in_stack;
    next_in_stack = next_in_stack->next_node;
  }
  return error;
}

/// @brief Ищет левые и правые скобки,проверяет их количество
int brackets_complects(StackNode *stack) {
  int error = 0;
  int cnt_left_bracket = 0;
  int cnt_right_bracket = 0;
  while (stack != NULL) {
    if (stack->priority == 6) {
      if (stack->node_data.d_symbol == '(') cnt_left_bracket++;
      if (stack->node_data.d_symbol == ')') cnt_right_bracket++;
    }
    stack = stack->next_node;
  }
  if (cnt_left_bracket != cnt_right_bracket) error = 1;
  return error;
}

/// @brief Перевод из инфиксного представления в
/// обратную польскую нотацию(ОПН) алгоритмом Sort Station
/// @return стэк, записанный ОПН, из элементов исходного стека

StackNode *reverse_polish_notation(StackNode **stack) {
  StackNode *arithmeticks = NULL, *result = NULL;
  StackNode *tmp = NULL;
  while (*stack != NULL) {
    tmp = *stack;
    *stack = (*stack)->next_node;
    if (tmp->priority < 1) {
      tmp->next_node = result;
      result = tmp;
    } else if (arithmeticks == NULL ||
               (arithmeticks->priority == 6 && tmp->priority != 6)) {
      move_from_stack(&arithmeticks, &tmp);
    } else if (tmp->priority == 6) {
      if (tmp->node_data.d_symbol == '(') {
        move_from_stack(&arithmeticks, &tmp);
      } else {
        free(tmp);
        while (arithmeticks != NULL &&
               arithmeticks->node_data.d_symbol != '(') {
          move_to_stack(&arithmeticks, &result);
        }
        arithmeticks = pop(arithmeticks);
      }
    } else if (tmp->priority > arithmeticks->priority) {
      move_from_stack(&arithmeticks, &tmp);
    } else {
      while (arithmeticks != NULL && arithmeticks->priority != 6 &&
             (tmp->priority < arithmeticks->priority ||
              (tmp->priority == arithmeticks->priority && tmp->priority != 3 &&
               tmp->priority != 5))) {
        move_to_stack(&arithmeticks, &result);
      }
      move_from_stack(&arithmeticks, &tmp);
    }
  }
  while (arithmeticks != NULL) {
    move_to_stack(&arithmeticks, &result);
  }
  return result;
}

/// @brief перемещает верхний элемент одного стека в другой,
/// исрользуется для переноса арифметический знаков в стек
void move_to_stack(StackNode **math, StackNode **result) {
  StackNode *tmp_stack = (*math)->next_node;
  (*math)->next_node = *result;
  *result = *math;
  *math = tmp_stack;
}

/// @brief перемещает верхний элемент из одного стека в другой
void move_from_stack(StackNode **math, StackNode **tmp) {
  (*tmp)->next_node = *math;
  *math = *tmp;
}

/// @brief Считает промежуточный результат операции и кладет
/// в ближайшее к оператору число
/// @param stack укзатель на оператор
/// @return ошибку вычисления
int find_tmp_result(StackNode *stack) {
  int error = 0;
  switch (stack->node_data.d_symbol) {
    case '-':
      find_tmp_minus(stack);
      break;
    case '+':
      find_tmp_plus(stack);
      break;
    case MOD:
      error = find_tmp_mod(stack);
      break;
    case '/':
      error = find_tmp_division(stack);
      break;
    case '*':
      find_tmp_multiplication(stack);
      break;
    case '^':
      find_tmp_degree(stack);
      break;
    case UO_MINUS:
      find_tmp_minus_uo(stack);
      break;
    case SIN:
      find_tmp_sin(stack);
      break;
    case COS:
      find_tmp_cos(stack);
      break;
    case TAN:
      find_tmp_tan(stack);
      break;
    case ASIN:
      error = find_tmp_asin(stack);
      break;
    case ACOS:
      error = find_tmp_acos(stack);
      break;
    case ATAN:
      find_tmp_atan(stack);
      break;
    case SQRT:
      error = find_tmp_sqrt(stack);
      break;
    case LN:
      error = find_tmp_ln(stack);
      break;
    case LOG:
      error = find_tmp_log(stack);
  }
  return error;
}

void find_tmp_minus(StackNode *stack) {
  double second_number = stack->next_node->node_data.d_number;
  double first_number = stack->next_node->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = first_number - second_number;
}

void find_tmp_plus(StackNode *stack) {
  double second_number = stack->next_node->node_data.d_number;
  double first_number = stack->next_node->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = first_number + second_number;
}

int find_tmp_mod(StackNode *stack) {
  int error = 0;
  double second_number = stack->next_node->node_data.d_number;
  double first_number = stack->next_node->next_node->node_data.d_number;
  if (second_number != 0) {
    stack->next_node->node_data.d_number = fmod(first_number, second_number);
  } else {
    error = 1;
  }
  return error;
}
int find_tmp_division(StackNode *stack) {
  int error = 0;
  double second_number = stack->next_node->node_data.d_number;
  double first_number = stack->next_node->next_node->node_data.d_number;
  if (second_number != 0) {
    stack->next_node->node_data.d_number = first_number / second_number;
  } else {
    error = 1;
  }
  return error;
}

void find_tmp_multiplication(StackNode *stack) {
  double second_number = stack->next_node->node_data.d_number;
  double first_number = stack->next_node->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = first_number * second_number;
}
void find_tmp_degree(StackNode *stack) {
  double second_number = stack->next_node->node_data.d_number;
  double first_number = stack->next_node->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = pow(first_number, second_number);
}

void find_tmp_minus_uo(StackNode *stack) {
  double number = stack->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = 0 - number;
}
void find_tmp_sin(StackNode *stack) {
  double number = stack->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = sin(number);
}
void find_tmp_cos(StackNode *stack) {
  double number = stack->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = cos(number);
}
void find_tmp_tan(StackNode *stack) {
  double number = stack->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = tan(number);
}
int find_tmp_asin(StackNode *stack) {
  int error = 0;
  double number = stack->next_node->node_data.d_number;
  if (number <= 1 && number >= -1) {
    stack->next_node->node_data.d_number = asin(number);
  } else {
    error = 1;
  }
  return error;
}
int find_tmp_acos(StackNode *stack) {
  int error = 0;
  double number = stack->next_node->node_data.d_number;
  if (number <= 1 && number >= -1) {
    stack->next_node->node_data.d_number = acos(number);
  } else {
    error = 1;
  }
  return error;
}

void find_tmp_atan(StackNode *stack) {
  double number = stack->next_node->node_data.d_number;
  stack->next_node->node_data.d_number = atan(number);
}
int find_tmp_sqrt(StackNode *stack) {
  int error = 0;
  double number = stack->next_node->node_data.d_number;
  if (number >= 0) {
    stack->next_node->node_data.d_number = sqrt(number);
  } else {
    error = 1;
  }
  return error;
}
int find_tmp_ln(StackNode *stack) {
  int error = 0;
  double number = stack->next_node->node_data.d_number;
  if (number > 0) {
    stack->next_node->node_data.d_number = log(number);
  } else {
    error = 1;
  }
  return error;
}
int find_tmp_log(StackNode *stack) {
  int error = 0;
  double number = stack->next_node->node_data.d_number;
  if (number > 0) {
    stack->next_node->node_data.d_number = log10(number);
  } else {
    error = 1;
  }
  return error;
}

/// @brief Удаляет оператор и один элемент,если операция бинарная
/// и не удаляет элемент, если унарная.
/// Связывает стэк после удаления элементов,
/// если есть начальный и/или если есть конечный узел
void remove_operator_and_element(StackNode *opr, StackNode **stack) {
  StackNode *tmp = *stack;
  int priority = opr->priority;
  if (opr != (*stack)) {
    while (tmp->next_node != opr) {
      tmp = tmp->next_node;
    }
    tmp->next_node = opr->next_node;
    tmp = tmp->next_node;
    free(opr);
  } else {
    *stack = pop(*stack);
    tmp = *stack;
  }
  if (priority < 4) {
    tmp->next_node = pop(tmp->next_node);
  }
}

// @brief Считает результат арифметического выражения
/// @param stack арифметическое выражение в ОПН
/// @param answer ответ
/// @return ошибку в случае вычисления
int calculate_answer(StackNode **stack, double *result) {
  int error = 0;
  StackNode *tmp = NULL, *tmp_res = NULL;
  *result = 0;
  while ((*stack)->next_node != NULL && error == 0) {
    tmp = *stack;
    while (tmp->next_node != NULL) {
      if (tmp->priority > 0) {
        tmp_res = tmp;
      }
      tmp = tmp->next_node;
    }
    error = find_tmp_result(tmp_res);
    if (error == 0) {
      remove_operator_and_element(tmp_res, stack);
    }
  }
  if (error == 0) {
    *result = (*stack)->node_data.d_number;
  }

  return error;
}

/// @brief Заменяет значение и тип всех элементов Х по шаблону
/// @param stack_copy Стэк
/// @param parameter_x шаблон подстановки для элементов Х
void set_x(StackNode *stack_copy, double parameter_x) {
  while (stack_copy != NULL) {
    if (stack_copy->priority == 0) {
      stack_copy->priority = -1;
      stack_copy->node_data.d_number = parameter_x;
    }
    stack_copy = stack_copy->next_node;
  }
}

/// @brief Заполняет координаты для графика по уравнению
/// @param rpn уравнение в ОПН
/// @param massive_x координаты Х
/// @param massive_y координаты  Y
/// @param x_min минимальное Х
/// @param x_max максимальное Х
void make_plot_coordinates(StackNode *rpn, double *massive_x, double *massive_y,
                           double x_min, double x_max) {
  double step = (x_max - x_min) / (1000 - 1);
  double tmp_x = x_min;
  int error = 0;
  double answer = NAN;
  massive_x[1000 - 1] = x_max;
  for (int i = 0; i < 1000; i++) {
    StackNode *stack_copy = NULL;
    if (i != 1000 - 1) massive_x[i] = tmp_x;
    copy_stack(rpn, &stack_copy);
    set_x(stack_copy, massive_x[i]);
    error = calculate_answer(&stack_copy, &answer);
    if (error == 1) {
      answer = NAN;
      massive_x[i] = answer;
    }
    massive_y[i] = answer;
    tmp_x += step;
    delete_stack(stack_copy);
  }
}

/// @brief Считает результат выражения, кладет его
/// в результат и возвращает ошибку
/// @param string выражение
/// @param answer ответ
/// @param parameter_x Х для подстановки
/// @param massive_x массив Х для графика
/// @param massive_y массив У для графика
/// @param x_min минимальное Х
/// @param x_max максимальное Х
/// @return 1 в случае ошибки, 0 в случае успеха, а
/// -1 в случае ошибки при подстановке Х
int s21_calculate_result(char *string, double *answer, double parameter_x,
                         double *massive_x, double *massive_y, double x_min,
                         double x_max) {
  *answer = 0;
  int error = 0;
  StackNode *stack = NULL, *rpn = NULL, *stack_copy = NULL;
  error = make_stack_from_string(string, &stack);
  if (error == 0) {
    rpn = reverse_polish_notation(&stack);
    if (check_x(rpn) == 0) {
      error = calculate_answer(&rpn, answer);
      for (int i = 0; i < 1000; i++) {
        massive_y[i] = *answer;
        massive_x[i] = x_max;
      }
      massive_x[0] = x_min;
    } else {
      copy_stack(rpn, &stack_copy);
      set_x(stack_copy, parameter_x);
      error = calculate_answer(&stack_copy, answer);
      if (error == 1) error = 1;
      make_plot_coordinates(rpn, massive_x, massive_y, x_min, x_max);
    }
  }
  delete_stack(stack_copy);
  delete_stack(stack);
  delete_stack(rpn);
  return error;
}
