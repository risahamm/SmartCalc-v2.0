#ifndef GRAPH_H
#define GRAPH_H

#include <qcustomplot.h>

#include <QDialog>

namespace Ui {
class Graph;
}

/**
 * @brief Class for displaying and managing graphical plots.
 * @details This class provides functionality for building and displaying plots
 * using QCustomPlot. It allows setting mathematical expressions, clearing the
 * plot, and retrieving the x-axis range.
 */
class Graph : public QDialog {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a Graph dialog.
   * @param parent pointer to the parent QWidget.
   */
  Graph(QWidget *parent = nullptr);

  /**
   * @brief Default destructor.
   */
  ~Graph();

 public slots:

  /**
   * @brief Builds a plot based on the provided coordinates.
   * @param coordinates pair of vectors representing the x and y coordinates.
   */
  void BuildPlot(
      std::pair<std::vector<double>, std::vector<double>> &coordinates);

  /**
   * @brief Sets the expression to be plotted.
   * @param expression QString representing the mathematical expression.
   */
  void SetExpression(QString expression);

  /**
   * @brief Removes all plotted data and resets the graph.
   */
  void Clear();

  /**
   * @brief Retrieves the current range of x-values for the plot.
   * @return pair of doubles representing the x-range.
   */
  std::pair<double, double> GetXRange();

 private:
  Ui::Graph *ui_;  ///< window interface
};

#endif  // GRAPH_H
