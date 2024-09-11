#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H

#include <list>
#include <stack>
#include <string>

#include "lexeme.h"

namespace s21 {

/**
 * @brief Class for converting an expression into Reversed Polish Notation
 * (RPN). This class takes a string expression, splits it into lexemes and
 * converts them into RPN. The result is stored in std::list container.
 * @details This class implements Dijkstra's algorithm or so called
 * "shunting-yard algorithm". The algorithm is is stack-based. There are two
 * text variables involved in the conversion: the input and the output list. The
 * conversion process uses the stack to store operations not yet added to the
 * output list. The conversion program sequentially reads each token from the
 * input string and on each step does certain actions based on which tokens have
 * been read.
 */
class ReversePolishNotation {
 public:
  /**
   * @brief Default constructor.
   */
  ReversePolishNotation() = default;
  /**
   * @brief Default destructor.
   */
  ~ReversePolishNotation() = default;

  /**
   * @brief Gets a list of lexemes in RPN.
   * @return std::list<Lexeme> list of lexemes representing the expression in
   * RPN.
   */
  std::list<Lexeme> GetRpnList() { return rpn_list_; };

  /**
   * @brief Converts a string into a list of separate lexemes converted into
   * RPN.
   * @param str expression to be converted into RPN.
   */
  void Convert(std::string &str);

 private:
  std::list<Lexeme> rpn_list_;  ///< list of separate lexemes converted into RPN

  /**
   * @brief Parses a number as a single lexeme and pushes it to the RPN List.
   * @param it pointer to the first digit of a number.
   * @return value to move the iterator in the string after parsing a lexeme.
   */
  size_t ParseNumber(std::string::iterator it);

  /**
   * @brief Parses an operator and pushes it to the stack.
   * @param operators_stack stack of operators.
   * @param it pointer to an element in the string.
   * @param str input string.
   */
  void ParseOperator(std::stack<Lexeme> &operators_stack,
                     std::string::iterator it, std::string &str);

  /**
   * @brief Pops and adds to RPN list everything until '(' is met.
   * @param operators_stack stack of operators.
   */
  void CloseParenth(std::stack<Lexeme> &operators_stack);

  /**
   * @brief Pushes opening parenthesis to the stack.
   * @param operators_stack stack of operators.
   */
  void PushOpenParenth(std::stack<Lexeme> &operators_stack);

  /**
   * @brief Checks the priority of the element.
   * @param it iterator to the element.
   * @return priority of the element.
   */
  Priority GetPriority(std::string::iterator it);

  /**
   * @brief Checks if `-` or `+` is unary.
   * @param it iterator to the element.
   * @param str input string.
   * @return true if unary, otherwise false.
   */
  bool IsUnary(std::string::iterator it, std::string &str);

};  // class ReversePolishNotation

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H