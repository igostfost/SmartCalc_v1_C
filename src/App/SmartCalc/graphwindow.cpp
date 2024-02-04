#include "graphwindow.h"
#include "ui_graphwindow.h"

extern "C"{
#include "../../s21_calc.h"
}


graphwindow::graphwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphwindow)
{
    ui->setupUi(this);
}

graphwindow::~graphwindow()
{
    delete ui;
}



void graphwindow::on_pushButton_back_clicked()
{
    this->close();
    emit MainWindow();
}

void graphwindow::pasteEquation(QString plotLine) {
    ui-> lineEdit_equation->setText(plotLine);

    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->replot();
}

void graphwindow::on_pushButton_create_clicked()
{
    double a = ui->lineEdit_left_xZone->text().toDouble();
    double b = ui->lineEdit_right_xZone->text().toDouble();
    int N = 1000;
    QVector<double> x(N), y(N);

    QString str = ui->lineEdit_equation->text();
    QByteArray ba = str.toLocal8Bit();
    char* equation = ba.data();
    double massive_x[1000];
    double massive_y[1000];
    double answer;
    s21_calculate_result(equation, &answer, 0, massive_x, massive_y, a, b);

    for (int i = 0; i < 1000; i++) {
        x[i] = massive_x[i];
        y[i] = massive_y[i];
    }

    ui->widget->clearGraphs();

    ui->widget->addGraph();


    ui->widget->graph(0)->setData(x, y);

    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(a, b);

    double minY = ui->lineEdit_left_yZone->text().toDouble();
    double maxY = ui->lineEdit_right_yZone->text().toDouble();
    ui->widget->yAxis->setRange(minY, maxY);

    ui->widget->replot();
}

