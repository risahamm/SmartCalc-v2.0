#include "calculation.h"

using namespace s21;

void Calculation::Parse(std::string &expression, long double x_value) {
  rpn_.Convert(expression);

  expression_ = rpn_.GetRpnList();
  long double operation_result = 0;
  std::stack<long double> numbers;
  Lexeme lexeme;
  long double number = 0;
  while (!expression_.empty()) {
    lexeme = expression_.front();
    expression_.pop_front();
    if (lexeme.type == LexemeType::kNumber) {
      if (lexeme.value == "x") {
        numbers.push(x_value);
      } else {
        number = std::stod(lexeme.value);
        numbers.push(number);
      }
    }
    if (lexeme.type == LexemeType::kOperator) {
      operation_result = Calculate(lexeme, numbers);
      numbers.push(operation_result);
    }
  }
  calculation_result_ = numbers.top();
  numbers.pop();
}

long double Calculation::Calculate(s21::Lexeme &current_operator,
                                   std::stack<long double> &numbers) {
  long double result = 0;
  long double a = numbers.top();
  long double b = 0;
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
      result = sinl(a);
    } else if (current_operator.value == "c") {
      result = cosl(a);
    } else if (current_operator.value == "t") {
      result = tanl(a);
    } else if (current_operator.value == "S") {
      result = asinl(a);
    } else if (current_operator.value == "C") {
      result = acosl(a);
    } else if (current_operator.value == "T") {
      result = atanl(a);
    } else if (current_operator.value == "l") {
      result = logl(a);
    } else if (current_operator.value == "L") {
      result = log10l(a);
    }
  }
  return result;
}

long double Calculation::GetResult() { return calculation_result_; }