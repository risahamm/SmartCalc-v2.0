#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H

#include <list>
#include <stack>
#include <string>
#include <stdexcept>

#include "cmath"
#include "lexeme.h"
#include "reverse_polish_notation.h"

namespace s21 {

/**
 * @brief Class that performs arithmetic and trigonometric calculations
 * based on mathematical expressions.
 * @details This class provides functionality to parse mathematical expressions,
 * convert them into Reverse Polish Notation (RPN), and compute the result.
 * It supports variable substitution for expressions containing a variable 'x'.
 * The result of the calculation can be retrieved using the GetResult method.
 */
class Calculation {
 public:
  /**
   * @brief Default constructor.
   */
  Calculation() = default;

  /**
   * @brief Default destructor.
   */
  ~Calculation() = default;

  /**
   * @brief Retrieves the result of calculation.
   * @return long double value representing the result of the calculation.
   */
  long double GetResult();

  /**
   * @brief Iterates through the expression, pushing numbers into stack and
   * performing calculations when operators are encountered.
   * @details Results of operations are also pushed into stack. At the end of
   * the parsing, the final result of the expression is stored in
   * calculation_result_.
   * @param expression input expression to be calculated.
   * @param x_value value of x variable.
   */
  void Parse(std::string &expression, long double x_value);

 private:
  ReversePolishNotation rpn_;  ///< class converting input expression into RPN
  std::list<Lexeme> expression_;    ///< expression in RPN to calculate
  long double calculation_result_;  ///< result of calculations

  /**
   * @brief Performs arithmetic and trigonometric calculations based on the
   * given operator and operands.
   * @param current_operator reference to the lexeme that contains the
   * operator to be applied.
   * @param numbers stack of double values representing the operands.
   * @return result of calculations as long double.
   */
  long double Calculate(s21::Lexeme &current_operator,
                        std::stack<long double> &numbers);

};  // class Calculation

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
