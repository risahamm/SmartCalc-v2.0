#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H

#include "../model/calculation.h"
//#include "../model/plot_graph.h"

namespace s21 {

class Controller {
 public:
  Controller(Calculation *calculation) : model_(calculation){};
  ~Controller() = default;

  long double Calculate(std::string expression, double x_value) {
    model_->Parse(expression, x_value);
    return model_->GetResult();
  }

//  std::vector<std::pair<long double, long double>> CalculateCoordinates(std::string &expression, std::pair<long double, long double> x_range) {
//    return plot_.CalculateY(expression, x_range);
//  }

 private:
  Calculation *model_;
//  PlotGraph plot_;

};  // class controller

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H
