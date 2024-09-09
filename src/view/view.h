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
  bool GetPointStatus(QString::iterator str);
  bool GetOperatorStatus(QString::iterator str);
  bool GetZeroStatus(QString::iterator str);
  bool GetNumStatus(QString::iterator str);
  bool GetXStatus(QString::iterator str);
  bool GetEStatus(QString::iterator str);
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
