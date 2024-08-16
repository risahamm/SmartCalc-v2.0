#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H

#include <list>
#include <stack>
#include <string>
#include "lexeme.h"

namespace s21 {

/**
 * @brief Class for converting an expression into Reversed Polish Notation (RPN).
 * @details This class takes a string expression and converts it to reverse Polish notation.
 * The result is stored in std::list container.
 */
class ReversePolishNotation {
 public:

  /**
   * @brief Parametrized constructor
   * @param input_str - string containing an expression to be converted
   */
  ReversePolishNotation(std::string const input_str) : str_(input_str) {
    rpn_list_ = Reverse();
  }

  /**
   * @brief Gets a list of lexemes in RPN
   * @return std::list<Lexeme> list of lexemes representing the expression in RPN
   */
  std::list<Lexeme> GetRpnList() { return rpn_list_; };

 private:
  std::list<Lexeme> rpn_list_; /// < list of separate lexemes converted into RPN
  std::string str_; /// < input string containing an expression to calculate

  /**
  * @brief Converts a string into a list of separate lexemes converted into RPN
  * @return std::list of lexemes converted into RPN
  */
  std::list<Lexeme> Reverse();

  /**
  * @brief Parses a number as a single lexeme and pushes it to the RPN List
  * @param it - pointer to the first digit of a number
  * @return value to move the iterator in the string after parsing a lexeme
  */
  size_t ParseNumber(std::string::iterator it);

  /**
  * @brief Parses an operator and pushes it to the stack
  * @param operators_stack - stack of operators
  * @param it - pointer to an element in the string
  */
  void ParseOperator(std::stack<Lexeme> &operators_stack,
                     std::string::iterator it);

  /**
  * @brief Pops and adds to RPN list everything until '(' is met
  * @param operators_stack - stack of operators
  */
  void CloseParenth(std::stack<Lexeme> &operators_stack);


  /**
  * @brief Pushes opening parenthesis to the stack
  * @param operators_stack
  */
  void PushOpenParenth(std::stack<Lexeme> &operators_stack);

  /**
  * @brief Checks the priority of the element
  * @param it - iterator to the element
  * @return Priority of the element
  */
  Priority GetPriority(std::string::iterator it);

  /**
  * @brief Checks if '-' or '+' is unary
  * @param it - iterator to the element
  * @return true if unary, otherwise false
  */
  bool IsUnary(std::string::iterator it);

};  // class ReversePolishNotation

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H