#include "mainwindow.h"

extern "C"{
#include "../../s21_calc.h"
}
#include "ui_mainwindow.h"
#include "graphwindow.h"
#include "creditwindow.h"
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_0_clicked() {
    ui->lineEdit_equation->insert("0");
}
void MainWindow::on_pushButton_1_clicked() {
    ui->lineEdit_equation->insert("1");
}
void MainWindow::on_pushButton_2_clicked() {
    ui->lineEdit_equation->insert("2");
}
void MainWindow::on_pushButton_3_clicked() {
    ui->lineEdit_equation->insert("3");
}
void MainWindow::on_pushButton_4_clicked() {
    ui->lineEdit_equation->insert("4");
}
void MainWindow::on_pushButton_5_clicked() {
    ui->lineEdit_equation->insert("5");
}
void MainWindow::on_pushButton_6_clicked() {
    ui->lineEdit_equation->insert("6");
}
void MainWindow::on_pushButton_7_clicked() {
    ui->lineEdit_equation->insert("7");
}
void MainWindow::on_pushButton_8_clicked() {
    ui->lineEdit_equation->insert("8");
}
void MainWindow::on_pushButton_9_clicked() {
    ui->lineEdit_equation->insert("9");
}
void MainWindow::on_pushButton_sin_clicked() {
    ui->lineEdit_equation->insert("sin(");
}
void MainWindow::on_pushButton_asin_clicked() {
    ui->lineEdit_equation->insert("asin(");
}
void MainWindow::on_pushButton_cos_clicked() {
    ui->lineEdit_equation->insert("cos(");
}
void MainWindow::on_pushButton_acos_clicked() {
    ui->lineEdit_equation->insert("acos(");
}
void MainWindow::on_pushButton_tan_clicked() {
    ui->lineEdit_equation->insert("tan(");
}
void MainWindow::on_pushButton_atan_clicked() {
    ui->lineEdit_equation->insert("atan(");
}
void MainWindow::on_pushButton_plus_clicked() {
    ui->lineEdit_equation->insert("+");
}
void MainWindow::on_pushButton_minus_clicked() {
    ui->lineEdit_equation->insert("-");
}
void MainWindow::on_pushButton_pow_clicked() {
    ui->lineEdit_equation->insert("^");
}
void MainWindow::on_pushButton_multiply_clicked() {
    ui->lineEdit_equation->insert("*");
}
void MainWindow::on_pushButton_divide_clicked() {
    ui->lineEdit_equation->insert("/");
}
void MainWindow::on_pushButton_mod_clicked() {
    ui->lineEdit_equation->insert("mod");
}
void MainWindow::on_pushButton_tochka_clicked() {
    ui->lineEdit_equation->insert(".");
}
void MainWindow::on_pushButton_x_clicked() {
    ui->lineEdit_equation->insert("x");
}
void MainWindow::on_pushButton_open_bracket_clicked() {
    ui->lineEdit_equation->insert("(");
}
void MainWindow::on_pushButton_close_bracket_clicked() {
    ui->lineEdit_equation->insert(")");
}
void MainWindow::on_pushButton_sqrt_clicked() {
    ui->lineEdit_equation->insert("sqrt(");
}
void MainWindow::on_pushButton_ln_clicked() {
    ui->lineEdit_equation->insert("ln(");
}
void MainWindow::on_pushButton_log_clicked() {
    ui->lineEdit_equation->insert("log(");
}
void MainWindow::on_pushButton_uo_minus_clicked()
{
    ui->lineEdit_equation->insert("-");
}

void MainWindow::on_pushButton_ac_clicked() {
    ui->lineEdit_equation->clear();
}

void MainWindow::on_pushButton_equal_clicked()
{
    double answer = 0;
    QString str = ui->lineEdit_equation->text();
    QString str2 = ui->lineEdit_equation->text();
    this->str2 = str2;
    int x_error = 0;

    QByteArray ba = str.toLocal8Bit();
    char* equation = ba.data();
    double massive_x[1000];
    double massive_y[1000];
    //double parameter_x = ui->lineEdit_x_param->text().toDouble();
    bool is_numeric = true;;
    QString inputText = ui->lineEdit_x_param->text();
    double parameter_x = 0.0;

    if (!inputText.isEmpty()) {
        parameter_x = inputText.toDouble(&is_numeric);
    }
    if (!is_numeric) {

        QMessageBox::critical(this, "Ошибка", "Некорректное значение Х! Проверьте поле X в нижнем левом углу.");
        x_error = 1;
    }

    if(x_error == 0){
    int error =
        s21_calculate_result(equation, &answer, parameter_x, massive_x, massive_y, -1, 1);
    if (error == 1) {
        //ui->lineEdit_equation->setText("error");
         QMessageBox::critical(this, "Ошибка", "Некорректное уравнение! Проверьте все скобки и аргументы функций.");
    } else {
        QString tmpStr = QString::number(answer);
        ui->lineEdit_equation->setText(tmpStr);
    }
    }
}


void MainWindow::on_pushButton_FUNCT_clicked()
{
    graphwindow* graphWindow = new graphwindow();
    connect(this, &MainWindow::signal_to_pasteEquation, graphWindow,
            &graphwindow::pasteEquation);
   //emit signal_to_pasteEquation(ui->lineEdit_equation->text());
   emit signal_to_pasteEquation(str2);
    graphWindow->show();

////   if (ui->lineEdit_equation->text() != "Waiting" &&
////        ui->lineEdit_equation->text() != "error") {
////        graphWindow->show();
////        emit signal_to_pasteEquation(ui->lineEdit_equation->text());
////        this->close();
////    }
}


void MainWindow::on_pushButton_CREDIT_clicked()
{
     CreditWindow* creditWindow = new CreditWindow();
    creditWindow->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        on_pushButton_equal_clicked();
    }

    QMainWindow::keyPressEvent(event);
}
