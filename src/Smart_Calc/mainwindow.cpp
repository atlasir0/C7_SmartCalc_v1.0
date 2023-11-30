#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_bracker_1, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_bracket_2, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(symbol()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(result_equal()));
  connect(ui->pushButton_equal_X, SIGNAL(clicked()), this,
          SLOT(result_equal_X()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear_all()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::symbol() {
  QPushButton *button = (QPushButton *)sender();
  QString text = ui->result_show->text() + button->text();
  ui->result_show->setText(text);
}

void MainWindow::clear_all() {
  ui->result_show->setText("");
  ui->result_show_X->setText("");
}

void MainWindow::result_equal() {
  QString str = ui->result_show->text();
  std::string str1 = str.toStdString();
  const char *input_str = str1.c_str();
  long double result = 0;
  int error = SmartCalc(input_str, &result);
  if (!error) ui->result_show->setText(QString::number(result, 'g', 10));
  if (error == -1) ui->result_show->setText("ERROR");
  if (error == -2) ui->result_show->setText("INF");
}

void MainWindow::result_equal_X() {
  QString str = ui->result_show->text();
  if (!str.isEmpty()) {
    std::string str1 = str.toStdString();
    const char *input_str = str1.c_str();
    long double result = 0;
    QString str_x = ui->result_show_X->text();
    static QRegularExpression regex("^[0-9.]+$");
    QRegularExpressionMatch match = regex.match(str_x);
    if (match.hasMatch()) {
      long double x = str_x.toDouble();
      int error = SmartCalc_X(input_str, &result, x);
      if (!error) ui->result_show->setText(QString::number(result, 'g', 10));
      if (error == -1) ui->result_show->setText("ERROR");
      if (error == -2) ui->result_show->setText("INF");
    } else
      ui->result_show->setText("ERROR");
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  QString line = ui->result_show->text();
  Graph *draw = new Graph;
  draw->draw(line.toStdString().c_str());
  draw->show();
}

void MainWindow::on_pushButton_CE_clicked()
{
    QString text = ui->result_show->text();
    if (!text.isEmpty()) {
      text.chop(1);
      ui->result_show->setText(text);
    }
}

