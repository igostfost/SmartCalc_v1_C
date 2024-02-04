#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "creditwindow.h"
#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QString str2;

  // signals:
  //     void openGraphWindow();

 private slots:
  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_plus_clicked();
  void on_pushButton_minus_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_multiply_clicked();
  void on_pushButton_divide_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_open_bracket_clicked();
  void on_pushButton_close_bracket_clicked();
  void on_pushButton_tochka_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_ac_clicked();
  void on_pushButton_uo_minus_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_FUNCT_clicked();

  void on_pushButton_CREDIT_clicked();
  void keyPressEvent(QKeyEvent *event);

 signals:
  void signal_to_pasteEquation(QString plotLine);
};
#endif  // MAINWINDOW_H
