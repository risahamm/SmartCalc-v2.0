#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <qcustomplot.h>


namespace Ui {
class Graph;
}

class View;

class Graph : public QDialog
{
    Q_OBJECT

public:

    Graph(QWidget *parent = nullptr);
    ~Graph();
    QString expression;


public slots:
    void BuildPlot();


private:
    Ui::Graph *ui_;

};


#endif // GRAPH_H
