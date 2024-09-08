#ifndef GRAPH_H
#define GRAPH_H

#include <qcustomplot.h>

#include <QDialog>

namespace Ui {
class Graph;
}

class View;

class Graph : public QDialog {
  Q_OBJECT

 public:
  Graph(QWidget *parent = nullptr);
  ~Graph();

 public slots:
  void BuildPlot();
  void SetExpression(QString expression);
  void Clear();

 private:
  Ui::Graph *ui_;
};

#endif  // GRAPH_H
