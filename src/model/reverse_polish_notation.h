//
// Created by Risa Hammond on 8/11/24.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++11-extensions"
#ifndef CPP3_SMARTCALC_V2_0_1_REVERSE_POLISH_NOTATION_H
#define CPP3_SMARTCALC_V2_0_1_REVERSE_POLISH_NOTATION_H

#include <iostream>
#include <list>
#include <stack>
#include <string>

namespace s21 {

enum class Priority {
  kPriority_0,  // numbers, parenthesis
  kPriority_1,  // +, -
  kPriority_2,  // *, /, %
  kPriority_3,  // pow, sqrt
  kPriority_4,  // cos, sin, tan, acos, asin, atan
};

enum class OperatorType {
  kMod = '%',
  kSqrt = 'r',
  kPow = '^',
  kLog = 'L',
  kLn = 'l',
  kSin = 's',
  kCos = 'c',
  kTan = 't',
  kAsin = 'S',
  kAcos = 'C',
  kAtan = 'T'
};

enum class LexemeType { kNumber, kOperator };

struct Lexeme {
  std::string value;
  Priority priority;
  LexemeType type;

  Lexeme()
      : value(" "),
        priority(Priority::kPriority_0),
        type(LexemeType::kNumber){};

  Lexeme(const Lexeme &other) { *this = other; }

  Lexeme &operator=(const Lexeme &other) {
    value = other.value;
    priority = other.priority;
    type = other.type;
    return *this;
  }
};

class ReversePolishNotation {
 public:
  ReversePolishNotation(std::string const input_str) : str_(input_str) {
    rpn_list_ = Reverse();
  }

  std::list<Lexeme> get_rpn_list() { return rpn_list_; };

 private:
  std::list<Lexeme> rpn_list_; /* list of separate lexemes converted into
                                  Reverse Polish Notation */
  std::string str_; /* input string containing an expression to calculate */

  std::list<Lexeme> Reverse();

  size_t ParseNumber(std::string::iterator it);
  size_t CloseParenth(std::stack<Lexeme> &operators_stack);
  size_t ParseOperator(std::stack<Lexeme> &operators_stack,
                       std::string::iterator it);

  bool IsUnary(std::string::iterator it);

};  // class ReversePolishNotation

/**
 * converts a string into a list of separate lexemes converted into Reverse
 * Polish Notation
 * @return list of lexemes converted into Reverse Polish Notation
 */
std::list<Lexeme> ReversePolishNotation::Reverse() {
  std::stack<Lexeme> operators;
  size_t move_iter =
      0; /* value to move an iterator in the string after parsing a lexeme */
  auto symbol = str_.begin();
  if (std::isdigit(*symbol) || *symbol == 'x') {
    move_iter = ParseNumber(symbol);
  } else if (*symbol == ')') {
    move_iter = CloseParenth(operators);
  } else {
    move_iter = ParseOperator(operators, symbol);
  }
  symbol += move_iter;
  return rpn_list_;
}

/**
 * parses a number as a single lexeme and pushes it to the Reverse Polish
 * Notation List
 * @param it - pointer to the first digit of a number
 * @return value to move an iterator in the string after parsing a lexeme
 */
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
  rpn_list_.push_back(new_lexeme);
  return (new_lexeme.value.length());
}

bool ReversePolishNotation::IsUnary(std::string::iterator it) {
  /* if the operator is first in the string */
  if (*it == *str_.begin()) {
    return true;
  }

  /* if the operator follows '(' */
  if (*(--it) == '(') {
    return true;
  }
  return false;
}

size_t ReversePolishNotation::CloseParenth(
    std::stack<Lexeme> &operators_stack) {
  Lexeme element;
  while (operators_stack.empty() == false) {
    element = operators_stack.top();
    if (element.value == "(") {
      operators_stack.pop();
      break;
    }
    rpn_list_.push_back(element);
    operators_stack.pop();
  }
  return 1;
}

size_t ReversePolishNotation::ParseOperator(std::stack<Lexeme> &operators_stack,
                                            std::string::iterator it) {
  size_t move_iter = 0;
  Lexeme new_element;
  //  if (*it == '-'  || *it == '+') { // TODO вынести в отдельн функцию
  //    new_element.priority = Priority::kPriority_1;
  //    move_iter = 1;
  //  } else if (*it == '*'  || *it == '/') {
  //    new_element.priority = Priority::kPriority_2;
  //    move_iter = 1;
  //  } else if ()
  Priority top_elem_priority = operators_stack.top().priority;
  if (operators_stack.empty() == true) {
    operators_stack.push(new_element);
  }
}

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_REVERSE_POLISH_NOTATION_H

#pragma clang diagnostic pop