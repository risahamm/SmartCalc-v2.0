#include "reverse_polish_notation.h"

using namespace s21;

void ReversePolishNotation::Convert(std::string &str) {
  std::stack<Lexeme> operators;

  size_t move_iter = 1;  ///< value to move the iterator
                         ///< in the string after parsing a lexeme

  std::string::iterator symbol = str.begin();
  while (symbol != str.end()) {
    move_iter = 1;
    if (std::isdigit(*symbol) || *symbol == 'x') {
      move_iter = ParseNumber(symbol);
    } else if (*symbol == '(') {
      PushOpenParenth(operators);
    } else if (*symbol == ')') {
      CloseParenth(operators);
    } else {
      ParseOperator(operators, symbol, str);
    }
    symbol += move_iter;
  }
  while (!operators.empty()) {
    rpn_list_.push_back(operators.top());
    operators.pop();
  }
}

size_t ReversePolishNotation::ParseNumber(std::string::iterator it) {
  Lexeme new_lexeme;

  /* check if a lexeme is a number or exponential notation or x */
  while (std::isdigit(*it) || *it == '.' || *it == 'e' ||
         (*it == '-' && *(it - 1) == 'e') || (*it == '+' && *(it - 1) == 'e') ||
         *it == 'x') {
    new_lexeme.value.push_back(*it);
    ++it;
  }
  new_lexeme.priority = Priority::kPriority_0;
  new_lexeme.type = LexemeType::kNumber;
  rpn_list_.push_back(new_lexeme);
  size_t move_iter = new_lexeme.value.length();
  return (move_iter);
}

void ReversePolishNotation::ParseOperator(std::stack<Lexeme> &operators_stack,
                                          std::string::iterator it,
                                          std::string &str) {
  Lexeme new_element(*it, GetPriority(it), LexemeType::kOperator);

  /* if `+` or `-` is an unary sign, push 0 to RPN list */
  if (IsUnary(it, str)) {
    Lexeme add_zero('0', Priority::kPriority_0, LexemeType::kNumber);
    rpn_list_.push_back(add_zero);
  }

  if (operators_stack.empty()) {
    operators_stack.push(new_element);

    /* if stack is not empty */
  } else {
    if (new_element.priority > operators_stack.top().priority) {
      operators_stack.push(new_element);
    } else {
      /* if current element priority is less or equal then top element priority,
       * pop and add top lexeme to the RPN list until '(' is met */
      while (!operators_stack.empty() &&
             (new_element.priority <= operators_stack.top().priority) &&
             operators_stack.top().value != "(") {
        Lexeme top_lexeme = operators_stack.top();
        rpn_list_.push_back(top_lexeme);
        operators_stack.pop();
      }
      operators_stack.push(new_element);
    }
  }
}

void ReversePolishNotation::CloseParenth(std::stack<Lexeme> &operators_stack) {
  Lexeme element;
  while (!operators_stack.empty()) {
    element = operators_stack.top();
    if (element.value == "(") {
      operators_stack.pop();
      break;
    }
    rpn_list_.push_back(element);
    operators_stack.pop();
  }
}

void ReversePolishNotation::PushOpenParenth(
    std::stack<Lexeme> &operators_stack) {
  Lexeme parenthesis('(', Priority::kPriority_0, LexemeType::kOperator);
  operators_stack.push(parenthesis);
}

Priority ReversePolishNotation::GetPriority(std::string::iterator it) {
  Priority element_priority;
  if (*it == '(') {
    element_priority = Priority::kPriority_0;
  } else if (*it == '+' || *it == '-') {
    element_priority = Priority::kPriority_1;
  } else if (*it == '*' || *it == '/' || *it == '%') {
    element_priority = Priority::kPriority_2;
  } else if (*it == static_cast<char>(OperatorType::kPow) ||
             *it == static_cast<char>(OperatorType::kSqrt)) {
    element_priority = Priority::kPriority_3;
  } else {
    element_priority = Priority::kPriority_4;
  }
  return element_priority;
}

bool ReversePolishNotation::IsUnary(std::string::iterator it,
                                    std::string &str) {
  if (*it == '+' || *it == '-') {
    /* if the operator is first in the string */
    if (it == str.begin()) {
      return true;
    }

    /* if the operator follows '(' */
    if (*(it - 1) == '(') {
      return true;
    }
  }
  return false;
}
