#include "graph.h"
#include "ui_graph.h"
#include "iostream"
#include "view.h"

bool Graph::instance_ = false;


Graph::Graph(QWidget *parent) : QDialog(parent), ui_(new Ui::Graph)
{

    if (!instance_) {
        std::cout << "contructor" << std::endl;
        ui_->setupUi(this);
        show();
        setWindowTitle("Graph");
        instance_ = true;
    }

}

Graph::~Graph()
{
    delete ui_;
    instance_ = false;

}
