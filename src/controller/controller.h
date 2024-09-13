#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H

#include "../model/calculation.h"
#include "../model/plot_graph.h"

namespace s21 {

/**
 * @brief Class that manages the interaction between the model and the view.
 * @details This class serves as a mediator between the calculation model
 * and graphic interface. It processes user input, performs calculations,
 * and retrieves graphical coordinates for plotting graphs.
 */
class Controller {
 public:
  /**
   * @brief Constructs a Controller with a given Calculation model.
   * @param calculation pointer to a Calculation object used for parsing
   * expressions and computing results.
   */
  Controller(Calculation *calculation) : model_(calculation){};

  /**
   * @brief Default destructor.
   */
  ~Controller() = default;

  /**
   * @brief Calculates the result of a mathematical expression.
   * @param expression string representing the mathematical expression to be
   * evaluated.
   * @param x_value x-value to substitute into the expression during evaluation.
   * @return computed result as a long double.
   */
  long double Calculate(std::string expression, double x_value) {
    model_->Parse(expression, x_value);
    return model_->GetResult();
  }

  /**
   * @brief Calculates the x and y coordinates for graphing based on the given
   * expression.
   * @param expression string representing the mathematical expression to be
   * evaluated.
   * @param x_range pair of long doubles representing the range of x-values.
   * @return pair of vectors containing the x-coordinates and corresponding
   * y-coordinates.
   */
  std::pair<std::vector<double>, std::vector<double>> CalculateGraphCoordinates(
      std::string &expression, std::pair<long double, long double> x_range) {
    return plot_.Calculate(expression, x_range);
  }

 private:
  Calculation
      *model_;  ///< pointer to the Calculation model for expression evaluation
  PlotGraph plot_;  ///< instance of PlotGraph for calculating graph coordinates

};  // class controller

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H
