#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <qcustomplot.h>

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

private:
    Ui::Graph *ui_;
};

#endif // GRAPH_H
