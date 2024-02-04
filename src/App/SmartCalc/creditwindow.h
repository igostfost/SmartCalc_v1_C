#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QMainWindow>

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private slots:
  void on_pushButton_calk_res_clicked();

  // void on_checkBox_AN_stateChanged(int arg1);

  // void on_checkBox_DIF_stateChanged(int arg1);

  void on_pushButton_back_clicked();

  void on_pushButton_clear_clicked();

 private:
  int type_payment;
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
