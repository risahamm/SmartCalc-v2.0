#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View view;
    view.show();
    view.setWindowTitle("SmartCalc");
    return a.exec();
}
