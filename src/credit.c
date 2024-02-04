#include "s21_calc.h"

/// @brief Рассчитывает ежемесячный платеж(первый и последний), общую сумму
/// выплат и переплату по кредиту
/// @param credit_sum кредит
/// @param credit_time срок кредита
/// @param percent ставка по кредиту
/// @param type_payment тип ежемесячного платежа, где 1-дифферинцированный и
/// 0-аннуитентный
/// @param first_payment первый ежемесячный платеж
/// @param last_payment последний ежемесячный платеж
/// @param overpayment переплата по кредиту
/// @param total_payment общая сумма выплат
void calculate_credit(double credit_sum, double credit_time, double percent,
                      int type_payment, double *first_payment,
                      double *last_payment, double *overpayment,
                      double *total_payment) {
  // double credit_sum = 120000;
  // double percent = 15;
  // double credit_time = 60;
  //   double total_payment = 0;
  // double first_payment = 0;
  // double last_payment = 0;
  //   double overpayment = 0;
  //   int type_payment = 0;
  double sd = credit_sum / credit_time;
  double sp = 1.0;
  double start_credit_sum = credit_sum;

  if (type_payment) {
    double days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i = 0;
    percent = percent / 100.0;
    *total_payment = 0.0;
    *first_payment = sd + credit_sum * percent * days[0] / 365.0;
    while (credit_sum > 0) {
      sp = credit_sum * percent * days[i] / 365.0;
      credit_sum = credit_sum - sd;
      *total_payment = *total_payment + sd + sp;
      if (i == 11) {
        i = 0;
      } else {
        i++;
      }
    }
    *last_payment = sp + sd;
  } else {
    percent = percent / 1200;
    *last_payment = *first_payment =
        credit_sum * percent / (1 - pow((1 + percent), (0 - credit_time)));
    *total_payment = *first_payment * credit_time;
  }

  *overpayment = *total_payment - start_credit_sum;
  //   printf("1 - %f\n last - %f\n total - %f\n over - %f\n", first_payment,
  //          last_payment, total_payment, overpayment);
}
