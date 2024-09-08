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

  std::vector<std::pair<long double, long double>> CalculateY(
      std::string &expression, std::pair<long double, long double> x_range);

 private:
  long double x_min_;
  long double x_max_;
  std::vector<std::pair<long double, long double>> coordinates_;
  Calculation calc_expression_;

};  // class PlotGraph

std::vector<std::pair<long double, long double>> PlotGraph::CalculateY(
    std::string &expression, std::pair<long double, long double> x_range) {
  x_min_ = x_range.first;
  x_max_ = x_range.second;

  long double y_coordinate = 0;
  long double x_coordinate = 0;
  long double step = 0.1;

  for (long double i = x_min_; i < x_max_; i += step) {
    calc_expression_.Parse(expression, i);
    y_coordinate = calc_expression_.GetResult();
    x_coordinate = i;
    coordinates_.push_back({x_coordinate, y_coordinate});
  }

  return coordinates_;
}

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOT_GRAPH_H