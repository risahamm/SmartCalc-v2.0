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
  Calculation(std::list<s21::Lexeme> rpn_list) : expression_(rpn_list) {}

  double Calculate();

 private:
  std::list<s21::Lexeme> expression_;  ///< expression in RPN to calculate
  double calculaton_result_;

  void Parse();

};  // class Calculation

void Calculation::Parse() {
  double result = 0;
  std::stack<double> numbers;
  s21::Lexeme lexeme;
  double number;
  while (!expression_.empty()) {
    lexeme = expression_.front();
    expression_.pop_front();
    if (lexeme.type == LexemeType::kNumber) {
      number = std::stod(lexeme.value);
      numbers.push(number);
    }
    if (lexeme.type == LexemeType::kOperator) {
      result += Calculate();
    }
  }
  calculaton_result_ = result;
}

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
