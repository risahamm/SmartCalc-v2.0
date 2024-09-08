#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOT_GRAPH_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOT_GRAPH_H

#include <string>
#include <vector>

#include "calculation.h"

namespace s21 {

class PlotGraph {
 public:
  PlotGraph() = default;

  ~PlotGraph() = default;

  std::pair<std::vector<double>, std::vector<double>> Calculate(
      std::string &expression, std::pair<double, double> x_range) {
    std::vector<double> x_vector;
    std::vector<double> y_vector;

    x_min_ = x_range.first;
    x_max_ = x_range.second;

    double y_coordinate = 0;
    double x_coordinate = 0;
    double step = 0.1;

    for (double i = x_min_; i < x_max_; i += step) {
      calc_expression_.Parse(expression, i);
      y_coordinate = static_cast<double>(calc_expression_.GetResult());
      x_coordinate = i;
      x_vector.push_back(x_coordinate);
      y_vector.push_back(y_coordinate);
    }

    return std::pair<std::vector<double>, std::vector<double>>{x_vector,
                                                               y_vector};
  }

 private:
  long double x_min_;
  long double x_max_;
  std::pair<std::vector<double>, std::vector<double>> coordinates_;
  Calculation calc_expression_;

};  // class PlotGraph

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOT_GRAPH_H
