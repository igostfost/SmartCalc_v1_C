#include "creditwindow.h"
#include "ui_creditwindow.h"
#include <QMessageBox>


extern "C"{
#include "../../s21_calc.h"
}

CreditWindow::CreditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreditWindow)
{
    ui->setupUi(this);
}

CreditWindow::~CreditWindow()
{
    delete ui;
}



void CreditWindow::on_pushButton_calk_res_clicked()
{
    double credit_sum = ui->lineEditcredit_sum->text().toDouble();
    double credit_time= ui->lineEdit_credit_time->text().toDouble();
    double percent = ui->lineEdit_percent->text().toDouble();
    double first_payment;
    double last_payment;
    double overpayment;
    double total_payment;
    int type_payment = 2;
    int error = 0;


    if (ui->checkBox_AN->isChecked() && ui->checkBox_DIF->isChecked()){
        QMessageBox::critical(this, "Ошибка", "Выбереите один варинат платежа : Аннуитетный или Дифференцированный");
          error = 1;

    }
    else if (ui->checkBox_AN->isChecked()) {
        type_payment = 0;
    }
    else if (ui->checkBox_DIF->isChecked()) {
            type_payment = 1;
        }
    if(error == 0){
    calculate_credit(credit_sum,credit_time,percent,
                     type_payment,&first_payment,&last_payment,
                     &overpayment, &total_payment);

   QString first = QString::number(first_payment,'f', 2);
    ui->lineEdit_first_paymen->setText(first);

    QString last = QString::number(last_payment,'f', 2);
    ui->lineEdit_last_payment->setText(last);

    QString total = QString::number(total_payment, 'f', 2);
    ui->lineEdit_total_payment->setText(total);

    QString over = QString::number(overpayment, 'f', 2);
    ui->lineEdit_overpayment->setText(over);
    }
    else {
    ui->lineEdit_first_paymen->clear();
    ui->lineEdit_last_payment->clear();
    ui->lineEdit_overpayment->clear();
    ui->lineEdit_total_payment->clear();
    }

}



//void CreditWindow::on_checkBox_AN_stateChanged(int arg1)
//{
//    if (ui->checkBox_AN->isChecked()) {
//        int type_payment = 0;
//    }

//}


//void CreditWindow::on_checkBox_DIF_stateChanged(int arg1)
//{
//    if (ui->checkBox_DIF->isChecked()) {
//        int type_payment = 0;
//    }
//}


void CreditWindow::on_pushButton_back_clicked()
{
    this->close();
    emit QMainWindow();

}

void CreditWindow::on_pushButton_clear_clicked()
{
    ui->lineEditcredit_sum->clear();
    ui->lineEdit_credit_time->clear();
    ui->lineEdit_percent->clear();
    ui->lineEdit_first_paymen->clear();
    ui->lineEdit_last_payment->clear();
    ui->lineEdit_overpayment->clear();
    ui->lineEdit_total_payment->clear();
}




