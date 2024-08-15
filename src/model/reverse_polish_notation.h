#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H

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
      : value(""), priority(Priority::kPriority_0), type(LexemeType::kNumber){};

  Lexeme(char new_value, Priority elem_priority, LexemeType elem_type)
      : priority(elem_priority), type(elem_type) {
    value.push_back(new_value);
  };

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

/**
 * converts a string into a list of separate lexemes converted into RPN
 * @return list of lexemes converted into RPN
 */
std::list<Lexeme> ReversePolishNotation::Reverse() {
  std::stack<Lexeme> operators;

  /* value to move the iterator in the string after parsing a lexeme */
  size_t move_iter = 1;

  auto symbol = str_.begin();
  while (symbol != str_.end()) {
    move_iter = 1;
    if (std::isdigit(*symbol) || *symbol == 'x') {
      move_iter = ParseNumber(symbol);
    } else if (*symbol == '(') {
      PushOpenParenth(operators);
    } else if (*symbol == ')') {
      CloseParenth(operators);
    } else {
      ParseOperator(operators, symbol);
    }
    symbol += move_iter;
  }
  while (!operators.empty()) {
    rpn_list_.push_back(operators.top());
    operators.pop();
  }
  return rpn_list_;
}

/**
 * parses a number as a single lexeme and pushes it to the RPN List
 * @param it - pointer to the first digit of a number
 * @return value to move the iterator in the string after parsing a lexeme
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
  new_lexeme.type = LexemeType::kNumber;
  rpn_list_.push_back(new_lexeme);
  size_t move_iter = new_lexeme.value.length();
  return (move_iter);
}

/**
 * checks if '-' or '+' is unary
 * @param it - iterator to the element
 * @return true if unary, otherwise false
 */
bool ReversePolishNotation::IsUnary(std::string::iterator it) {
  if (*it == '+' || *it == '-') {
    /* if the operator is first in the string */
    if (*it == *str_.begin()) {
      return true;
    }

    /* if the operator follows '(' */
    if (*(--it) == '(') {
      return true;
    }
  }
  return false;
}

/**
 * pops and adds to RPN list everything until '(' is met
 * @param operators_stack - stack of operators
 */
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

/**
 * parses an operator and pushes it to the stack
 * @param operators_stack - stack of operators
 * @param it - pointer to an element in the string
 */
void ReversePolishNotation::ParseOperator(std::stack<Lexeme> &operators_stack,
                                          std::string::iterator it) {
  Lexeme new_element(*it, GetPriority(it), LexemeType::kOperator);

  /* if + or - is an unary sign, push 0 to RPN list */
  if (IsUnary(it)) {
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
    }
  }
}

/**
 * checks the priority of the element
 * @param it - iterator to the element
 * @return Priority of the element
 */
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

/**
 * pushes opening parenthesis to the stack
 * @param operators_stack
 */
void ReversePolishNotation::PushOpenParenth(
    std::stack<Lexeme> &operators_stack) {
  Lexeme parenthesis('(', Priority::kPriority_0, LexemeType::kOperator);
  operators_stack.push(parenthesis);
}

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_REVERSE_POLISH_NOTATION_H