#include "view.h"

#include <iostream>

#include "./ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent), controller_(controller), ui_(new Ui::View) {
  ui_->setupUi(this);

  QRegularExpressionValidator *regexXValidator =
      new QRegularExpressionValidator(QRegularExpression(
          "^(-?100000000000(\\.0{1,6})?|(-?[0-9]{1,11})(\\.[0-9]{1,6})?)$"));
  ui_->x_value_input->setValidator(regexXValidator);

  std::vector<QPushButton *> num_buttons = {
      ui_->zero_button,  ui_->one_button,  ui_->two_button, ui_->three_button,
      ui_->four_button,  ui_->five_button, ui_->six_button, ui_->seven_button,
      ui_->eight_button, ui_->nine_button};
  for (QPushButton *num_button : num_buttons) {
    QObject::connect(num_button, SIGNAL(clicked()), this,
                     SLOT(NumberClicked()));
  }

  std::vector<QPushButton *> plus_minus_operators = {ui_->minus_button,
                                                     ui_->plus_button};
  for (QPushButton *op_button : plus_minus_operators) {
    QObject::connect(op_button, SIGNAL(clicked()), this,
                     SLOT(PlusMinusOperatorClicked()));
  }

  std::vector<QPushButton *> mul_div_operators = {ui_->multiply_button,
                                                  ui_->divide_button};
  for (QPushButton *mul_div_op_button : mul_div_operators) {
    QObject::connect(mul_div_op_button, SIGNAL(clicked()), this,
                     SLOT(MulDivOperatorClicked()));
  }

  std::vector<QPushButton *> math_functions = {
      ui_->tan_button,  ui_->cos_button,  ui_->sin_button, ui_->atan_button,
      ui_->acos_button, ui_->asin_button, ui_->log_button, ui_->ln_button};
  for (QPushButton *function_button : math_functions) {
    QObject::connect(function_button, SIGNAL(clicked()), this,
                     SLOT(MathFunctionClicked()));
  }

  connect(ui_->clear_button, SIGNAL(clicked()), this,
          SLOT(ClearButtonClicked()));
  connect(ui_->point_button, SIGNAL(clicked()), this,
          SLOT(PointButtonClicked()));
  connect(ui_->open_parenthesis_button, SIGNAL(clicked()), this,
          SLOT(OpenParenthesisButtonClicked()));
  connect(ui_->close_parenthesis_button, SIGNAL(clicked()), this,
          SLOT(CloseParenthesisButtonClicked()));
  connect(ui_->x_button, SIGNAL(clicked()), this, SLOT(XButtonClicked()));
  connect(ui_->mod_button, SIGNAL(clicked()), this, SLOT(ModButtonClicked()));
  connect(ui_->pow_button, SIGNAL(clicked()), this, SLOT(PowButtonClicked()));
  connect(ui_->sqrt_button, SIGNAL(clicked()), this, SLOT(SqrtButtonClicked()));
  connect(ui_->e_button, SIGNAL(clicked()), this, SLOT(EButtonClicked()));
  connect(ui_->backspace_button, SIGNAL(clicked()), this,
          SLOT(BackspaceClicked()));
  connect(ui_->equal_button, SIGNAL(clicked()), this,
          SLOT(EqualButtonClicked()));
  connect(ui_->graphing, SIGNAL(clicked()), this, SLOT(OpenGraphWindow()));
}

View::~View() { delete ui_; }

void View::ClearButtonClicked() {
  string_to_calculate_.clear();
  string_to_show_.clear();
  ui_->display->setText("0");
  ui_->x_value_input->clear();
  num_clicked_ = false;
  point_clicked_ = false;
  operator_clicked_ = false;
  x_clicked_ = false;
  open_parenthesis_clicked_ = 0;
  flag_first_zero_ = false;
  e_clicked_ = false;
  GetAllFlags();
}

void View::NumberClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  if (string_to_calculate_.length() != 0 && point_clicked_ == false &&
      string_to_calculate_.back() == '0' && button->text() == '0' &&
      flag_first_zero_ == false) {
    flag_first_zero_ = false;
  }

  if (string_to_calculate_.length() != 0 && point_clicked_ == false &&
      button->text() != '0') {
    if (string_to_calculate_.back() == '0' && flag_first_zero_ == false) {
      string_to_calculate_.chop(1);
      string_to_show_.chop(1);
    }

    flag_first_zero_ = true;
  }

  if ((flag_first_zero_ == true ||
       (num_clicked_ == false || point_clicked_ == true)) &&
      button->text() != '0') {
    if (string_to_calculate_.length() == 0) {
      string_to_calculate_ += button->text();
      string_to_show_ += button->text();
      ui_->display->setText(string_to_show_);
      num_clicked_ = true;
      operator_clicked_ = false;
      flag_first_zero_ = true;

    } else if (string_to_calculate_.length() != 0 &&
               string_to_calculate_.back() != ')' &&
               string_to_calculate_.back() != 'x') {
      string_to_calculate_ += button->text();
      string_to_show_ += button->text();
      ui_->display->setText(string_to_show_);
      num_clicked_ = true;
      operator_clicked_ = false;
      flag_first_zero_ = true;
    }

  } else if ((flag_first_zero_ == true ||
              (num_clicked_ == false || point_clicked_ == true)) &&
             button->text() == '0') {
    if (string_to_calculate_.length() == 0) {
      string_to_calculate_ += button->text();
      string_to_show_ += button->text();
      ui_->display->setText(string_to_show_);
      num_clicked_ = true;
      operator_clicked_ = false;

    } else if (string_to_calculate_.length() != 0 &&
               string_to_calculate_.back() != ')' &&
               string_to_calculate_.back() != 'x') {
      string_to_calculate_ += button->text();
      string_to_show_ += button->text();
      ui_->display->setText(string_to_show_);
      num_clicked_ = true;
      operator_clicked_ = false;
    }
  }
  GetAllFlags();
}

void View::PlusMinusOperatorClicked() {
  if (string_to_calculate_.length() != 0 && operator_clicked_ == false &&
      string_to_calculate_.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (string_to_calculate_.back() != 'e') {
      e_clicked_ = false;
    }

    string_to_calculate_ += button->text();
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    num_clicked_ = false;
    flag_first_zero_ = false;
    point_clicked_ = false;
    operator_clicked_ = true;
    x_clicked_ = false;

  } else if (string_to_calculate_.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += button->text();
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    operator_clicked_ = true;
  }
  GetAllFlags();
}

void View::MulDivOperatorClicked() {
  if (operator_clicked_ == false && string_to_calculate_.length() != 0 &&
      string_to_calculate_.back() != '(' &&
      string_to_calculate_.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (button->text() == "×") {
      string_to_calculate_ += "*";

    } else if (button->text() == "÷") {
      string_to_calculate_ += "/";
    }

    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    num_clicked_ = false;
    point_clicked_ = false;
    operator_clicked_ = true;
    x_clicked_ = false;
  }
  GetAllFlags();
}

void View::MathFunctionClicked() {
  bool flag = false;
  if (string_to_calculate_.length() != 0) {
    if (num_clicked_ == false && point_clicked_ == false &&
        string_to_calculate_.back() != 'x' &&
        string_to_calculate_.back() != ')') {
      flag = true;
      QPushButton *button = qobject_cast<QPushButton *>(sender());
      string_to_calculate_ += button->text() + "(";
      string_to_show_ += button->text() + "(";
      ui_->display->setText(string_to_show_);
      open_parenthesis_clicked_++;
      num_clicked_ = false;
      operator_clicked_ = false;
      e_clicked_ = false;
    }

  } else if ((operator_clicked_ == true || string_to_calculate_.length() == 0 ||
              open_parenthesis_clicked_ > 0) &&
             !flag) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += button->text() + "(";
    string_to_show_ += button->text() + "(";
    ui_->display->setText(string_to_show_);
    open_parenthesis_clicked_++;
    num_clicked_ = false;
    operator_clicked_ = false;
  }
  GetAllFlags();
}

void View::OpenParenthesisButtonClicked() {
  if (string_to_calculate_.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += button->text();
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    open_parenthesis_clicked_++;

  } else if (string_to_calculate_.length() != 0 &&
             (operator_clicked_ == true || open_parenthesis_clicked_ > 0) &&
             string_to_calculate_.back() != 'x' && num_clicked_ == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += button->text();
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    open_parenthesis_clicked_++;
    operator_clicked_ = false;
    num_clicked_ = false;
  }
  GetAllFlags();
}

void View::CloseParenthesisButtonClicked() {
  if (open_parenthesis_clicked_ > 0 && string_to_calculate_.back() != '.' &&
      (num_clicked_ == true || string_to_calculate_.back() == ')' ||
       x_clicked_ == true)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += button->text();
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    open_parenthesis_clicked_--;
    operator_clicked_ = false;
  }
  GetAllFlags();
}

void View::PointButtonClicked() {
  if (num_clicked_ == true && point_clicked_ == false &&
      string_to_calculate_.back() != ')' && e_clicked_ == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += button->text();
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    point_clicked_ = true;
  }
  GetAllFlags();
}

void View::ModButtonClicked() {
  if (operator_clicked_ == false &&
      (num_clicked_ == true || x_clicked_ == true) &&
      string_to_calculate_.back() != '.' && e_clicked_ == false) {
    string_to_calculate_ += "%";
    string_to_show_ += "%";
    ui_->display->setText(string_to_show_);
    operator_clicked_ = true;
    point_clicked_ = false;
    num_clicked_ = false;
    x_clicked_ = false;
  }
  GetAllFlags();
}

void View::PowButtonClicked() {
  if (string_to_calculate_.length() != 0 &&
      string_to_calculate_.back() != '.' &&
      string_to_calculate_.back() != 'e' &&
      (num_clicked_ == true || string_to_calculate_.back() == ')' ||
       string_to_calculate_.back() == 'x')) {
    string_to_calculate_ += "^(";
    string_to_show_ += "^(";
    ui_->display->setText(string_to_show_);
    open_parenthesis_clicked_++;
    num_clicked_ = false;
    x_clicked_ = false;
  }
  GetAllFlags();
}

void View::SqrtButtonClicked() {
  if (string_to_calculate_.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += "r(";
    string_to_show_ += button->text() + "(";
    ui_->display->setText(string_to_show_);
    open_parenthesis_clicked_++;
    operator_clicked_ = false;

  } else if (string_to_calculate_.length() != 0 &&
             (operator_clicked_ == true ||
              string_to_calculate_.back() == '(')) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += "r(";
    string_to_show_ += button->text() + "(";
    ui_->display->setText(string_to_show_);
    point_clicked_ = false;
    open_parenthesis_clicked_++;
    operator_clicked_ = false;
  }
  GetAllFlags();
}

void View::XButtonClicked() {
  if ((string_to_calculate_.length() == 0 || operator_clicked_ == true) ||
      (open_parenthesis_clicked_ > 0 && num_clicked_ == false &&
       x_clicked_ == false)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate_ += "x";
    string_to_show_ += button->text();
    ui_->display->setText(string_to_show_);
    x_clicked_ = true;
    operator_clicked_ = false;
    num_clicked_ = false;
  }
  GetAllFlags();
}

void View::EButtonClicked() {
  if (e_clicked_ == false && num_clicked_ == true && point_clicked_ == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_show_ += button->text();
    string_to_calculate_ += button->text();
    ui_->display->setText(string_to_show_);
    e_clicked_ = true;
  }
  GetAllFlags();
}

void View::ChopString(size_t number_to_chop) {
  string_to_calculate_.chop(number_to_chop);
  string_to_show_.chop(number_to_chop);
}

void View::BackspaceClicked() {
  if (string_to_calculate_.length() != 0) {
    if (string_to_calculate_.length() == 1) {
      ClearButtonClicked();
      return;
    }

    QString last_five_chars = string_to_calculate_.right(5);
    QString last_four_chars = string_to_calculate_.right(4);
    QString last_three_chars = string_to_calculate_.right(3);
    QString last_two_chars = string_to_calculate_.right(2);

    if (string_to_calculate_.back() == '.') {
      ChopString(1);
      point_clicked_ = false;
      QString::ConstIterator str = string_to_calculate_.end() - 1;
      flag_first_zero_ = GetZeroStatus(str);

    } else if (string_to_calculate_.back() == '%' ||
               string_to_calculate_.back() == '+' ||
               string_to_calculate_.back() == '-' ||
               string_to_calculate_.back() == '*' ||
               string_to_calculate_.back() == '/') {
      ChopString(1);
      QString::ConstIterator str = string_to_calculate_.end() - 1;
      point_clicked_ = GetPointStatus(str);
      flag_first_zero_ = GetZeroStatus(str);
      e_clicked_ = GetEStatus(str);

    } else if (string_to_calculate_.back() == ')') {
      ChopString(1);
      open_parenthesis_clicked_++;

    } else if (string_to_calculate_.back() == 'x') {
      string_to_calculate_.chop(1);
      string_to_show_.chop(2);

    } else if (string_to_calculate_.back() == 'e') {
      ChopString(1);
      e_clicked_ = false;

    } else if (last_five_chars == "acos(" || last_five_chars == "asin(" ||
               last_five_chars == "atan(") {
      ChopString(5);
      open_parenthesis_clicked_--;

    } else if (last_four_chars == "cos(" || last_four_chars == "sin(" ||
               last_four_chars == "tan(" || last_four_chars == "log(") {
      ChopString(4);
      open_parenthesis_clicked_--;

    } else if (last_three_chars == "ln(") {
      ChopString(3);
      open_parenthesis_clicked_--;

    } else if (last_two_chars == "^(" || last_two_chars == "r(") {
      ChopString(2);
      open_parenthesis_clicked_--;

    } else if (string_to_calculate_.back() == '(') {
      ChopString(1);
      open_parenthesis_clicked_--;

    } else { /* if number */

      ChopString(1);
    }

    if (string_to_calculate_.length() == 0) {
      ClearButtonClicked();

    } else {
      ui_->display->setText(string_to_show_);
      QString::ConstIterator str = string_to_calculate_.end() - 1;
      num_clicked_ = GetNumStatus(str);
      operator_clicked_ = GetOperatorStatus(str);
      x_clicked_ = GetXStatus(str);
    }

  } else { /* string is empty */

    ClearButtonClicked();
  }
  GetAllFlags();
}

bool View::GetPointStatus(QString::ConstIterator str) {
  while (!str->isNull() && *str != '+' && *str != '-' && *str != '*' &&
         *str != '/' && *str != '(' && *str != ')') {
    if (*str == '.') {
      return true;
      break;
    }
    --str;
  }

  return false;
}

bool View::GetOperatorStatus(QString::ConstIterator str) {
  if (!str->isNull() &&
      (*str == '+' || *str == '-' || *str == '*' || *str == '/')) {
    return true;
  }

  return false;
}

bool View::GetZeroStatus(QString::ConstIterator str) {
  /* if removed symbol isn't point */
  if (!str->isNull() && *str == '0') {
    return false;

    /* if removed symbol is point */
  } else if (!str->isNull() && *str == '.') {
    if (*(--str) == '0') {
      if (!(str - 1)->isNull() && (*(str - 1) == '+' || *(str - 1) == '-' ||
                                   *(str - 1) == '*' || *(str - 1) == '/')) {
        return false;

      } else if ((str - 1)->isNull()) {
        return false;
      }
    }
  }

  return true;
}

bool View::GetNumStatus(QString::ConstIterator str) {
  if (!str->isNull() && str->isDigit() || *str == '.') {
    return true;
  }

  return false;
}

bool View::GetXStatus(QString::ConstIterator str) {
  if (!str->isNull() && *str == 'x') {
    return true;
  }

  return false;
}

bool View::GetEStatus(QString::ConstIterator str) {
  if (!str->isNull() && *str == 'e') {
    return true;
  }

  str -= 2;

  if (!str->isNull() && *str == 'e') {
    return true;
  }

  return false;
}

void View::EqualButtonClicked() {
  if (open_parenthesis_clicked_ == 0 && string_to_calculate_.length() != 0 &&
      operator_clicked_ == false) {
    s21::FormatString formatted_str(string_to_calculate_);
    long double x_value = ui_->x_value_input->text().toDouble();
    std::cout << "formatted_str: " << formatted_str.GetString() << std::endl;
    long double result =
        controller_->Calculate(formatted_str.GetString(), x_value);

    SetResult(result);
  }
}

void View::SetResult(long double &result) {
  /* clear all flags */
  ClearButtonClicked();

  if (std::isinf(result) || std::isnan(result)) {
    ui_->display->setText("calculation error");

  } else {
    long double truncated_result = truncl(result);

    /* if result is float */
    if (fabs(result - truncated_result) > 1e-7) {
      string_to_calculate_ = TruncateZeros(result);
      point_clicked_ = true;

      /* if result is integer */
    } else {
      string_to_calculate_ = QString::number(result, 'L', 0);
    }

    /* if result is too long for display window, use scientific notation */
    if (string_to_calculate_.length() >= 21) {
      string_to_calculate_ = QString::number(result, 'e', 0);
      e_clicked_ = true;
    }

    string_to_show_ = string_to_calculate_;
    num_clicked_ = true;

    if (result != 0) {
      flag_first_zero_ = true;
    }

    ui_->display->setText(string_to_show_);
  }
}

QString View::TruncateZeros(long double &value) {
  QString str_value = QString::number(value, 'f', 7);
  QString::iterator it = (str_value.end() - 1);

  while (*it == '0') {
    it--;
    str_value.chop(1);
  }

  return str_value;
}

void View::OpenGraphWindow() {
  /* if the window isn't open */
  if (graph_ == nullptr) {
    graph_ = new Graph(this);

    int main_window_x = this->x();
    int main_window_y = this->y();

    connect(graph_, &Graph::finished, this, &View::GraphWindowClosed);

    graph_->move(main_window_x + this->width() + 20, main_window_y);
    graph_->show();

    /* if the window is already open */
  } else {
    graph_->raise();
    graph_->activateWindow();
  }

  /* if expression is valid */
  if (open_parenthesis_clicked_ == 0 && string_to_calculate_.length() != 0 &&
      operator_clicked_ == false) {
    graph_->SetExpression(string_to_show_);

    s21::FormatString formatted_str(string_to_calculate_);
    std::string str_to_plot = formatted_str.GetString();
    std::pair<std::vector<double>, std::vector<double>> coordinates =
        controller_->CalculateGraphCoordinates(str_to_plot,
                                               graph_->GetXRange());

    graph_->BuildPlot(coordinates);

  } else if (string_to_calculate_.length() != 0) {
    graph_->Clear();
    graph_->SetExpression("invalid input");

    /* input string is empty */
  } else {
    graph_->Clear();
  }
}

void View::GraphWindowClosed() { graph_ = nullptr; }

void View::GetAllFlags() {
  std::cout << "-----------------------------" << std::endl;
  std::cout << "string: " << string_to_calculate_.toStdString() << std::endl;
  std::cout << "num_clicked_: " << num_clicked_ << std::endl;
  std::cout << "point_clicked_: " << point_clicked_ << std::endl;
  std::cout << "operator_clicked_: " << operator_clicked_ << std::endl;
  std::cout << "open_parenthesis_clicked_: " << open_parenthesis_clicked_
            << std::endl;
  std::cout << "x_clicked_: " << x_clicked_ << std::endl;
  std::cout << "e_clicked_: " << e_clicked_ << std::endl;
  std::cout << "flag_first_zero_: " << flag_first_zero_ << std::endl;
}
