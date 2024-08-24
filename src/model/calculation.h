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

  double Calculate(s21::Lexeme &current_operator, std::stack<double> &numbers);

  double GetResult() { return calculaton_result_; }

 private:
  std::list<Lexeme> expression_;  ///< expression in RPN to calculate
  double calculaton_result_;

  void Parse();

};  // class Calculation

void Calculation::Parse() {
  double operation_result = 0;
  std::stack<double> numbers;
  Lexeme lexeme;
  double number;
  while (!expression_.empty()) {
    lexeme = expression_.front();
    expression_.pop_front();
    if (lexeme.type == LexemeType::kNumber) {
      number = std::stod(lexeme.value);
      numbers.push(number);
    }
    if (lexeme.type == LexemeType::kOperator) {
      operation_result = Calculate(lexeme, numbers);
      numbers.push(operation_result);
    }
  }
  calculaton_result_ = numbers.top();
  numbers.pop();
}

double Calculation::Calculate(s21::Lexeme &current_operator,
                              std::stack<double> &numbers) {
  double result = 0;
  double a = numbers.top();
  double b = 0;
  numbers.pop();

  /* operations that require two operands */
  if (current_operator.priority == Priority::kPriority_1 ||
      current_operator.priority == Priority::kPriority_2) {
    b = numbers.top();
    numbers.pop();
    if (current_operator.value == "+") {
      result = b + a;
    } else if (current_operator.value == "-") {
      result = b - a;
    } else if (current_operator.value == "*") {
      result = b * a;
    } else if (current_operator.value == "/") {
      result = b / a;
    } else if (current_operator.value == "%") {
      if (a == 0.0) {
        result = NAN;
      } else {
        result = static_cast<int>(b) % static_cast<int>(a);
      }
    }

    /* operations that require one operand (except pow) */
  } else {
    if (current_operator.value == "r") {
      result = sqrt(a);
    } else if (current_operator.value == "^") {
      b = numbers.top();
      numbers.pop();
      result = pow(b, a);
    } else if (current_operator.value == "s") {
      result = sin(a);
    } else if (current_operator.value == "c") {
      result = cos(a);
    } else if (current_operator.value == "t") {
      result = tan(a);
    } else if (current_operator.value == "S") {
      result = asin(a);
    } else if (current_operator.value == "C") {
      result = acos(a);
    } else if (current_operator.value == "T") {
      result = atan(a);
    }
  }
  return result;
}

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
