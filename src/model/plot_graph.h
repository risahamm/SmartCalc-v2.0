#ifndef CPP3_SMARTCALC_V2_0_SRC_MODEL_PLOT_GRAPH_H_
#define CPP3_SMARTCALC_V2_0_SRC_MODEL_PLOT_GRAPH_H_

#include <string>
#include <vector>

#include "calculation.h"

namespace s21 {

/**
 * @brief Class for calculating and storing coordinates for graphing.
 * @details This class takes a mathematical expression and a range of x-values,
 * computes the corresponding y-values using the provided expression,
 * and stores the resulting coordinates in vectors for further use,
 * which is plotting a graph.
 */
class PlotGraph {
 public:
  /**
   * @brief Default constructor.
   */
  PlotGraph() = default;

  /**
   * @brief Default destructor.
   */
  ~PlotGraph() = default;

  /**
   * @brief Calculates the x and y coordinates for the given expression over the
   * specified range.
   * @param expression string representing mathematical expression.
   * @param x_range pair of doubles representing the range of x-values.
   * @return pair of vectors containing the x-coordinates and corresponding
   * y-coordinates.
   */
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
  long double x_min_;  ///< min x-value
  long double x_max_;  ///< max x-value
  std::pair<std::vector<double>, std::vector<double>>
      coordinates_;  ///< coordinates for plotting
  Calculation
      calc_expression_;  ///< instance of Calculation to evaluate expressions

};  // class PlotGraph

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_MODEL_PLOT_GRAPH_H_
