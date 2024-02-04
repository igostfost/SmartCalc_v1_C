#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class graphwindow;
}

class graphwindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit graphwindow(QWidget *parent = nullptr);
  ~graphwindow();

 signals:
  void MainWindow();

 private slots:

  void on_pushButton_back_clicked();

  void on_pushButton_create_clicked();

 public slots:
  void pasteEquation(QString plotLine);

 private:
  Ui::graphwindow *ui;
};

#endif  // GRAPHWINDOW_H
