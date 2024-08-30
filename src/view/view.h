#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QStack>

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
  // void EqualButtonClicked();
  // void BuildPlot();

 private:
  Ui::View *ui;
  QString string_to_calculate;
  QString expression_string;
  bool num_clicked = false;
  bool point_clicked = false;
  bool operator_clicked = false;
  int open_parenthesis_clicked = 0;
  bool x_clicked = false;
  bool e_clicked = false;
  bool flag_first_zero = false;
  QStack<unsigned int> last_lexeme_size;
  QStack<std::pair<std::string, bool>> flags;
};
#endif  // VIEW_H
