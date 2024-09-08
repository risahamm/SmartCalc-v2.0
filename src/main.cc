#include <QApplication>

#include "controller/controller.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  s21::Calculation calculation;
  s21::Controller controller(&calculation);

  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/pics/calculator_icon.png"));
  View view(nullptr, &controller);
  view.show();
  view.setWindowTitle("SmartCalc");

  return a.exec();
}
