#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 public slots:
  void numberClicked();
  void plusMinusOperatorClicked();
  void mulDivOperatorClicked();
  void mathFunctionClicked();
  void clearButtonClicked();
  void openParenthesisButtonClicked();
  void closeParenthesisButtonClicked();
  void pointButtonClicked();
  void modButtonClicked();
  void powButtonClicked();
  void sqrtButtonClicked();
  void xButtonClicked();
  // void equalButtonClicked();
  // void buildPlot();

 private:
  Ui::View *ui;
  QString stringToCalculate;
  bool num_clicked = false;
  bool point_clicked = false;
  bool operator_clicked = false;
  int open_parenthesis_clicked = 0;
  bool x_clicked = false;
  bool flag_first_zero = false;
};
#endif  // VIEW_H
