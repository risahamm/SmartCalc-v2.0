#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H

#include <list>
#include <stack>
#include <string>
#include "lexeme.h"

namespace s21 {

class ReversePolishNotation {
 public:
  ReversePolishNotation(std::string const input_str) : str_(input_str) {
    rpn_list_ = Reverse();
  }

  std::list<Lexeme> GetRpnList() { return rpn_list_; };

 private:
  std::list<Lexeme> rpn_list_; /* list of separate lexemes converted into RPN */
  std::string str_; /* input string containing an expression to calculate */

  std::list<Lexeme> Reverse();

  size_t ParseNumber(std::string::iterator it);
  void CloseParenth(std::stack<Lexeme> &operators_stack);
  void ParseOperator(std::stack<Lexeme> &operators_stack,
                     std::string::iterator it);
  bool IsUnary(std::string::iterator it);
  void PushOpenParenth(std::stack<Lexeme> &operators_stack);
  Priority GetPriority(std::string::iterator it);

};  // class ReversePolishNotation

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H