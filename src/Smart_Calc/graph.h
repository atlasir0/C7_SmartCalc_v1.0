#ifndef GRAPH_H
#define GRAPH_H

#include <qcustomplot.h>

#include <QVector>
#include <QWidget>

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void draw(const char *str);

 private:
  Ui::Graph *ui;
};

#endif  // GRAPH_H
