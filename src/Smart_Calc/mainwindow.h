#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graph.h>
#include <locale.h>

#include <QMainWindow>
#include <QWindow>

extern "C" {
#include <../s21_calc.h>
#include <../s21_stack.h>
}
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

 private slots:
  void symbol();
  void clear_all();
  void result_equal();
  void result_equal_X();
  void on_pushButton_graph_clicked();
  void on_pushButton_CE_clicked();
};
#endif  // MAINWINDOW_H
