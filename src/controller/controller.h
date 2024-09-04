#ifndef CPP3_SMARTCALC_V2_0_1_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CONTROLLER_H

#include "../model/calculation.h"

namespace s21 {

class Controller {
 public:
  Controller(Calculation *calculation) : model_(calculation){};
  ~Controller() = default;

  double Calculate(std::string expression, double x_value) {
    model_->Parse(expression, x_value);
    return model_->GetResult();
  }

 private:
  Calculation *model_;

};  // class controller

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CONTROLLER_H
