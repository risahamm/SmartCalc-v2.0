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


private:
    Ui::Graph *ui_;
    static bool instance_;
};


#endif // GRAPH_H
