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
  /**
   * @brief Constructs a View class instance that represents the main user
   * interface.
   * @param parent QMainWindow to inherit from.
   * @param controller pointer to Controller class instance.
   */
  View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);

  /**
   * Default destructor.
  ~View();

 public slots:
  /**
   * @brief Handles clicked number-buttons, including zero as a first digit in a
 number-lexeme to avoid multiple print.
   */
  void NumberClicked();

  /**
   * @brief Handles addition and subtraction buttons clicked.
   */
  void PlusMinusOperatorClicked();

  /**
   * @brief Handles multiplication and division buttons clicked.
   */
  void MulDivOperatorClicked();

  /**
   * @brief Handles 'sin', 'cos', 'tan', 'asin', 'acos', 'atan', 'ln', 'log'
   * buttons clicked.
   */
  void MathFunctionClicked();

  /**
   * @brief Handles 'Clear All' button clicked.
   */
  void ClearButtonClicked();

  /**
   * @brief Handles opening parenthesis button clicked.
   */
  void OpenParenthesisButtonClicked();

  /**
   * @brief Handles closing parenthesis button clicked.
   */
  void CloseParenthesisButtonClicked();

  /**
   * @brief Handles point button clicked.
   */
  void PointButtonClicked();

  /**
   * @brief Handles 'mod' button clicked.
   */
  void ModButtonClicked();

  /**
   * @brief Handles 'pow' button clicked.
   */
  void PowButtonClicked();

  /**
   * @brief Handles 'sqrt' button clicked.
   */
  void SqrtButtonClicked();

  /**
   * @brief Handles 'x' button clicked.
   */
  void XButtonClicked();

  /**
   * @brief Handles 'e' button clicked.
   */
  void EButtonClicked();

  /**
   * @brief Handles 'backspace' button clicked.
   */
  void BackspaceClicked();

  /**
   * @brief Handles '=' button clicked.
   */
  void EqualButtonClicked();

  /**
   * @brief Handles Graphing button clicked.
   */
  void OpenGraphWindow();

 private slots:

  /**
   * @brief Sets Graphing window instance to nullptr.
   */
  void GraphWindowClosed();

  /**
   * @brief Chops string_to_calculate_ and string_to_show_ by specified number
   * of symbols.
   * @param number_to_chop number of symbols to chop.
   */
  void ChopString(size_t number_to_chop);

  /**
   * @brief Retrieves last point-lexeme status.
   * @param str iterator to the current symbol in string_to_calculate_.
   * @return true - point clicked, otherwise - false.
   */
  bool GetPointStatus(QString::ConstIterator str);

  /**
   * @brief Retrieves last operator-lexeme status.
   * @param str iterator to the current symbol in string_to_calculate_.
   * @return true - operator clicked, otherwise - false.
   */
  bool GetOperatorStatus(QString::ConstIterator str);

  /**
   * @brief Retrieves first zero in a lexeme status.
   * @param str iterator to the current symbol in string_to_calculate_.
   * @return true - enable multiple zero input, false - disable
   */
  bool GetZeroStatus(QString::ConstIterator str);

  /**
   * @brief Retrieves last number-lexeme status.
   * @param str iterator to the current symbol in string_to_calculate_.
   * @return true - number clicked, otherwise - false.
   */
  bool GetNumStatus(QString::ConstIterator str);

  /**
   * @brief Retrieves last x-lexeme status.
   * @param str iterator to the current symbol in string_to_calculate_.
   * @return true - 'x' clicked, otherwise - false.
   */
  bool GetXStatus(QString::ConstIterator str);

  /**
   * @brief Retrieves last 'e' button status.
   * @param str iterator to the current symbol in string_to_calculate_.
   * @return true - 'e' clicked, otherwise - false.
   */
  bool GetEStatus(QString::ConstIterator str);

  /**
   * @brief Handles the way the result of calculation will be sent to UI.
   * @details Configurates the calculation result to be presented as an integer
   * or floating point number or scientific notation if exceeds display
   * capacity. Treats exceptions as 'calculation error'.
   * @param result string representing result of calculation to be sent to UI.
   */
  void SetResult(long double &result);

  /**
   * @brief Truncates extra zero-digits at the end of a floating point number.
   * @param value value to truncate.
   * @return truncated value.
   */
  QString TruncateZeros(long double &value);

  /**
   * @brief FOR DEBUG. Retrieves all flags statuses and currents
   * string_to_calculate_ state and prints to the output stream.
   */
  void GetAllFlags();

 private:
  Ui::View *ui_;                 ///< pointer to UI instance
  Graph *graph_ = nullptr;       ///< pointer to Graphing window
  s21::Controller *controller_;  ///< pointer to Controller class instance
  QString string_to_calculate_;  ///< string representation of an expression to
                                 ///< calculate, processed for parsing
  QString string_to_show_;  ///< string representation of an expression to send
                            ///< to UI
  bool num_clicked_ = false;       ///< flag indicating number-lexeme status
  bool point_clicked_ = false;     ///< flag indicating point status
  bool operator_clicked_ = false;  ///< flag indicating operator status
  bool x_clicked_ = false;         ///< flag indicating x-variable status
  bool e_clicked_ =
      false;  ///< flag indicating 'e' status for scientific notation
  bool flag_first_zero_ = false;  ///< flag indicating status of '0' as a first
                                  ///< digit in a number-lexeme
  int open_parenthesis_clicked_ = 0;  ///< counter of parentheses
};

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_VIEW_H
