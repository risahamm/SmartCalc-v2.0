#include <QApplication>

#include "controller/controller.h"
#include "model/calculation.h"
#include "model/reverse_polish_notation.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  s21::ReversePolishNotation rpn;
  s21::Calculation calculation(rpn);
  s21::Controller controller(&calculation);


  QApplication a(argc, argv);
  View view(nullptr, &controller);
  view.show();
  view.setWindowTitle("SmartCalc");

  return a.exec();
}
