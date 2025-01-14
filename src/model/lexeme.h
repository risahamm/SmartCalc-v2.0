#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_LEXEME_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_LEXEME_H_

#include <string>

namespace s21 {

/**
 * @brief Represents the priority levels of operators.
 * @details This enum class defines the priority levels for different operators
 * and parentheses in expressions. Higher values indicate higher precedence.
 */
enum class Priority {
  kPriority_0,  ///< numbers, parenthesis
  kPriority_1,  ///< addition and subtraction (+, -)
  kPriority_2,  ///< multiplication, division, and modulus (*, /, %)
  kPriority_3,  ///< power and square root (pow, sqrt)
  kPriority_4,  ///< trigonometric functions (cos, sin, tan, acos, asin, atan)
};

/**
 * @brief Represents the type of a lexeme.
 */
enum class LexemeType { kNumber, kOperator };

/**
 * @brief Class represents a single lexeme in an expression.
 * @details This class encapsulates the properties of a lexeme, including its
 * value, priority, and type. It is used in the context of parsing and
 * evaluating expressions.
 */
class Lexeme {
 public:
  std::string value;  ///< string representation of the lexeme
  Priority priority;  ///< priority level of the lexeme
  LexemeType type;    ///< type of the lexeme

  /**
   * @brief Default constructor.
   */
  Lexeme()
      : value(""), priority(Priority::kPriority_0), type(LexemeType::kNumber){};

  /**
   * @brief Parameterized constructor.
   * @param new_value character value of the lexeme.
   * @param elem_priority priority of the lexeme.
   * @param elem_type type of the lexeme.
   */
  Lexeme(char new_value, Priority elem_priority, LexemeType elem_type)
      : priority(elem_priority), type(elem_type) {
    value.push_back(new_value);
  };

  /**
   * @brief Copy constructor.
   * @param other other lexeme to copy from.
   */
  Lexeme(const Lexeme &other) { *this = other; }

  /**
   * @brief Default destructor.
   */
  ~Lexeme() = default;

  /**
   * @brief Assignment operator.
   * @param other other lexeme to assign from.
   * @return reference to this lexeme after assignment.
   */
  Lexeme &operator=(const Lexeme &other) = default;
};  // class Lexeme

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_LEXEME_H_
