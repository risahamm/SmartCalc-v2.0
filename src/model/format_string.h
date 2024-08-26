#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_FORMAT_STRING_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_FORMAT_STRING_H

#include <locale>
#include <string>

namespace s21 {

/**
 * @brief Class for converting an input string into a string suitable
 * for calculation.
 * @details This class takes a string of wide characters and converts it
 * into basic string suitable for calculation. It transforms wide symbol into
 * standard char and formats string for calculations.
 */
class FormatString {
 public:
  /**
   * @brief Parametrized constructor
   * @param input_str - wstring to be converted
   */
  FormatString(std::wstring const input_str) : wide_str_(input_str) {
    Convert();
  }

  /**
   * @brief Default destructor
   */
  ~FormatString() = default;

  /**
   * @brief Accessor
   * @return std::string expression suitable for calculation
   */
  std::string GetString() { return basic_str_; }

 private:
  std::string basic_str_;  ///< result of convertion
  std::wstring wide_str_;  ///< input string to be converted

  /**
   * @brief Converts wstring into a string suitable for calculation
   * @return std::string expression to be calculated
   */
  std::string Convert();

};  // class wide_string_to_basic

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_FORMAT_STRING_H
