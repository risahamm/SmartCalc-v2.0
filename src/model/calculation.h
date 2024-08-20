#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H

#include <list>
#include <string>

namespace s21 {

class Calculation {
 public:

  /**
   * @brief Parametrized constructor
   * @param rpn_list - expression in RPN to be calculated
   */
  Calculation (std::list<std::string> rpn_list) : expression_(rpn_list) {}


 private:
  std::list<std::string> expression_; ///< expression in RPN to calculate

}; // class Calculation

} // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CALCULATION_H


