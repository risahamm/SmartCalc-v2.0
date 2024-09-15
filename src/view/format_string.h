#ifndef CPP3_SMARTCALC_V2_0_SRC_VIEW_FORMAT_STRING_H_
#define CPP3_SMARTCALC_V2_0_SRC_VIEW_FORMAT_STRING_H_

#include <QString>
#include <locale>
#include <string>

namespace s21 {

/**
 * @brief Class for converting an input QString into std::string suitable
 * for calculation.
 * @details This class takes a string of characters and converts it
 * into basic string suitable for calculation. It shortens long lexemes and
 * prepares the string for parsing.
 */
class FormatString {
 public:
  /**
   * @brief Parametrized constructor.
   * @param input_str QString to be converted.
   */
  FormatString(QString const input_str) : q_str_(input_str), basic_str_("") {
    Convert();
  }

  /**
   * @brief Default destructor.
   */
  ~FormatString() = default;

  /**
   * @brief Accessor.
   * @return std::string expression suitable for calculation.
   */
  std::string GetString() { return basic_str_; }

 private:
  std::string basic_str_;  ///< result of convertion
  QString q_str_;          ///< input string to be converted

  /**
   * @brief Converts QString into std::string suitable for calculation.
   */
  void Convert();

};  // class FormatString

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_VIEW_FORMAT_STRING_H_
