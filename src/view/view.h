#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_VIEW_H
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_VIEW_H

#include <QMainWindow>
#include <QStack>

#include "../controller/controller.h"
#include "format_string.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

/**
 * @brief Class representing the main user interface of the calculator
 * application.
 * @details This class provides the graphical user interface for the calculator.
 * It handles user interactions, displays results, and manages the graphing
 * window for plotting mathematical functions.
 */
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
  ~View();

 public slots:
  void NumberClicked();
  void PlusMinusOperatorClicked();
  void MulDivOperatorClicked();
  void MathFunctionClicked();
  void ClearButtonClicked();
  void OpenParenthesisButtonClicked();
  void CloseParenthesisButtonClicked();
  void PointButtonClicked();
  void ModButtonClicked();
  void PowButtonClicked();
  void SqrtButtonClicked();
  void XButtonClicked();
  void EButtonClicked();
  void BackspaceClicked();
  void EqualButtonClicked();
  void OpenGraphWindow();

 private slots:
  void GraphWindowClosed();
  void ChopString(size_t number_to_chop);
  bool GetPointStatus(QString::ConstIterator str);
  bool GetOperatorStatus(QString::ConstIterator str);
  bool GetZeroStatus(QString::ConstIterator str);
  bool GetNumStatus(QString::ConstIterator str);
  bool GetXStatus(QString::ConstIterator str);
  bool GetEStatus(QString::ConstIterator str);
  void SetResult(long double &result);
  QString TruncateZeros(long double &value);

  void GetAllFlags();

 private:
  Ui::View *ui_;
  Graph *graph_ = nullptr;
  s21::Controller *controller_;
  QString string_to_calculate_;
  QString string_to_show_;
  bool num_clicked_ = false;
  bool point_clicked_ = false;
  bool operator_clicked_ = false;
  bool x_clicked_ = false;
  bool e_clicked_ = false;
  bool flag_first_zero_ = false;
  int open_parenthesis_clicked_ = 0;
};

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_VIEW_H
