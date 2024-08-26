#include "calculation.h"

using namespace s21;

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
  calculaton_result_ = std::to_string(numbers.top());
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

std::string Calculation::GetResult() {
  if (calculaton_result_ == "NAN") {
    calculaton_result_ = "Calculation error";
  }
  return calculaton_result_;
}