#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H

#include <list>
#include <stack>
#include <string>

#include "lexeme.h"

namespace s21 {

class Calculation {
 public:
  /**
   * @brief Parametrized constructor
   * @param rpn_list - expression in RPN to be calculated
   */
  Calculation(std::list<Lexeme> rpn_list)
      : expression_(rpn_list), calculaton_result_(0) {
    Parse();
  }

  /**
   * @brief Default destructor
   */
  ~Calculation() = default;

  /**
   * @brief Retrieves the result of calculation
   * @return string representing the result of the last calculation or an error message if applicable
   */
  std::string GetResult();

 private:
  std::list<Lexeme> expression_;  ///< expression in RPN to calculate
  std::string calculaton_result_; ///< result of calculations

  /**
   * @brief Iterates through the expression, pushing numbers into stack and performing calculations
   * when operators are encountered.
   * @details Results of operations are also pushed into stack. At the end of the parsing,
   * the final result of the expression is stored as a string in calculation_result_
   */
  void Parse();

  /**
   * @brief Performs arithmetic and trigonometric calculations based on the given operator and operands
   * @param current_operator - reference to the lexeme that contains the operator to be applied
   * @param numbers - stack of double values representing the operands
   * @return result of calculations as a double
   */
  double Calculate(s21::Lexeme &current_operator, std::stack<double> &numbers);

};  // class Calculation

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
