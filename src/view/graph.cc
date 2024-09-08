#include "graph.h"

#include <qcustomplot.h>

#include "ui_graph.h"
#include "view.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui_(new Ui::Graph) {
  ui_->setupUi(this);
  setWindowTitle("Graph");
}

Graph::~Graph() { delete ui_; }

void Graph::BuildPlot(
    std::pair<std::vector<double>, std::vector<double>> &coordinates) {
  ui_->plot->clearGraphs();

  double x_begin = ui_->spin_box_min_x->value();
  double x_end = ui_->spin_box_max_x->value();
  double y_begin = ui_->spin_box_min_y->value();
  double y_end = ui_->spin_box_max_y->value();

  QVector<double> x_vector(coordinates.first.begin(), coordinates.first.end());
  QVector<double> y_vector(coordinates.second.begin(),
                           coordinates.second.end());

  ui_->plot->xAxis->setRange(x_begin, x_end);
  ui_->plot->yAxis->setRange(y_begin, y_end);

  ui_->plot->addGraph();
  ui_->plot->graph(0)->setData(x_vector, y_vector);
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

std::pair<double, double> Graph::GetXRange() {
  std::pair<double, double> x_range;
  x_range.first = ui_->spin_box_min_x->value();
  x_range.second = ui_->spin_box_max_x->value();
  return x_range;
}
