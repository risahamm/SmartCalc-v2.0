#include "graph.h"
#include "ui_graph.h"
#include "iostream"
#include "view.h"


Graph::Graph(QWidget *parent) : QDialog(parent), ui_(new Ui::Graph)
{

        ui_->setupUi(this);
        setWindowTitle("Graph");

        connect(ui_->create_plot, SIGNAL(clicked()), this,
                SLOT(BuildPlot()));


}

Graph::~Graph()
{
    delete ui_;

}

void Graph::BuildPlot() {

    std::cout << "check" << std::endl;
    ui_->expression_to_plot->setText(expression);
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
