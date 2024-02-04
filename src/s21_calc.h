
#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#define L 255
#define TOL 0.000001

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int fix_string(char *string, char **result);
void find_unarity(char *string);
int to_stack(char *string, StackNode **stack);
int make_stack_from_string(char *string, StackNode **stack);
void have_case_minus(StackNode *stack);
void have_case_plus(StackNode *stack);
void have_case_division(StackNode *stack);
void have_case_multiplication(StackNode *stack);
void have_case_degree(StackNode *stack);
void have_case_left_bracket(StackNode *stack);
void have_case_right_bracket(StackNode *stack);
void have_case_plus_uo(StackNode *stack);
void have_case_minus_uo(StackNode *stack);
void have_case_x(StackNode *stack);
int have_case_mod(StackNode *stack, char *string, int *i);
int have_case_s(StackNode *stack, char *string, int *i);
int have_case_cos(StackNode *stack, char *string, int *i);
int have_case_tan(StackNode *stack, char *string, int *i);
int have_case_a(StackNode *stack, char *string, int *i);
int have_case_l(StackNode *stack, char *string, int *i);
int have_case_number(StackNode *stack, char *string, int *i);
void reverse_stack(StackNode **stack);
int check_x(StackNode *stack);
int check_left_symbol(StackNode *stack);
int check_right_symbol(StackNode *stack);
int brackets_complects(StackNode *stack);
StackNode *reverse_polish_notation(StackNode **stack);
void move_to_stack(StackNode **math, StackNode **result);
void move_from_stack(StackNode **math, StackNode **tmp);
int find_tmp_result(StackNode *stack);
void find_tmp_minus(StackNode *stack);
void find_tmp_plus(StackNode *stack);
int find_tmp_mod(StackNode *stack);
int find_tmp_division(StackNode *stack);
void find_tmp_multiplication(StackNode *stack);
void find_tmp_degree(StackNode *stack);
void find_tmp_minus_uo(StackNode *stack);
void find_tmp_sin(StackNode *stack);
void find_tmp_cos(StackNode *stack);
void find_tmp_tan(StackNode *stack);
int find_tmp_asin(StackNode *stack);
int find_tmp_acos(StackNode *stack);
void find_tmp_atan(StackNode *stack);
int find_tmp_sqrt(StackNode *stack);
int find_tmp_ln(StackNode *stack);
int find_tmp_log(StackNode *stack);
void remove_operator_and_element(StackNode *opr, StackNode **stack);
int calculate_answer(StackNode **stack, double *result);
int s21_calculate_result(char *string, double *answer, double parameter_x,
                         double *massive_x, double *massive_y, double x_min,
                         double x_max);
void make_plot_coordinates(StackNode *rpn, double *massive_x, double *massive_y,
                           double x_min, double x_max);
void set_x(StackNode *stack_copy, double parameter_x);
void calculate_credit(double credit_sum, double credit_time, double percent,
                      int type_payment, double *first_payment,
                      double *last_payment, double *overpayment,
                      double *total_payment);

#endif  // SRC_S21_CALC_H_
