#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QDialog>
#include <QRegularExpressionValidator>
#include <iostream>

namespace Ui {
class credit_calc;
}

class credit_calc : public QDialog {
  Q_OBJECT

 public:
  explicit credit_calc(QWidget *parent = nullptr);
  ~credit_calc();

 private:
  Ui::credit_calc *ui;
  QRegularExpressionValidator input_validator;

 private slots:
  void credit_calculator();
  void on_pushButton_annuity_clicked();
};

#endif  // CREDIT_CALC_H
