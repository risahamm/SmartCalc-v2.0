#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_LEXEME_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_LEXEME_H

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
}; // class Lexeme

} // namespace s21

#endif CPP3_SMARTCALC_V2_0_1_SRC_MODEL_LEXEME_H // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_LEXEME_H