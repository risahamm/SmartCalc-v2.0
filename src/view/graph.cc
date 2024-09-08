#include "graph.h"

#include "iostream"
#include "ui_graph.h"
#include "view.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui_(new Ui::Graph) {
  ui_->setupUi(this);
  setWindowTitle("Graph");
}

Graph::~Graph() { delete ui_; }

void Graph::BuildPlot() {
  long double x_begin = ui_->spin_box_min_x->value();
  long double x_end = ui_->spin_box_max_x->value();
  long double y_begin = ui_->spin_box_min_y->value();
  long double y_end = ui_->spin_box_max_y->value();

  ui_->plot->xAxis->setRange(x_begin, x_end);
  ui_->plot->yAxis->setRange(y_begin, y_end);

  ui_->plot->addGraph();
  ui_->plot->replot();
  ui_->plot->update();

  ui_->plot->setInteraction(QCP::iRangeZoom, true);
  ui_->plot->setInteraction(QCP::iRangeDrag, true);
}

void Graph::SetExpression(QString expression) {
  ui_->expression_to_plot->setText(expression);
}

void Graph::Clear() {
  ui_->expression_to_plot->clear();
  ui_->plot->clearGraphs();
  ui_->plot->replot();
  ui_->plot->update();
}
