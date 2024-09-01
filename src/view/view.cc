#include "view.h"

#include <iostream>

#include "./ui_view.h"

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);

  QRegularExpressionValidator *regexXValidator =
      new QRegularExpressionValidator(QRegularExpression(
          "^(-?100000000000(\\.0{1,6})?|(-?[0-9]{1,11})(\\.[0-9]{1,6})?)$"));
  ui->x_value_input->setValidator(regexXValidator);

  std::vector<QPushButton *> num_buttons = {
      ui->zero_button,  ui->one_button,  ui->two_button, ui->three_button,
      ui->four_button,  ui->five_button, ui->six_button, ui->seven_button,
      ui->eight_button, ui->nine_button};
  for (QPushButton *num_button : num_buttons) {
    QObject::connect(num_button, SIGNAL(clicked()), this,
                     SLOT(NumberClicked()));
  }

  std::vector<QPushButton *> plus_minus_operators = {ui->minus_button,
                                                     ui->plus_button};
  for (QPushButton *op_button : plus_minus_operators) {
    QObject::connect(op_button, SIGNAL(clicked()), this,
                     SLOT(PlusMinusOperatorClicked()));
  }

  std::vector<QPushButton *> mul_div_operators = {ui->multiply_button,
                                                  ui->divide_button};
  for (QPushButton *mul_div_op_button : mul_div_operators) {
    QObject::connect(mul_div_op_button, SIGNAL(clicked()), this,
                     SLOT(MulDivOperatorClicked()));
  }

  std::vector<QPushButton *> math_functions = {
      ui->tan_button,  ui->cos_button,  ui->sin_button, ui->atan_button,
      ui->acos_button, ui->asin_button, ui->log_button, ui->ln_button};
  for (QPushButton *function_button : math_functions) {
    QObject::connect(function_button, SIGNAL(clicked()), this,
                     SLOT(MathFunctionClicked()));
  }

  connect(ui->clear_button, SIGNAL(clicked()), this,
          SLOT(ClearButtonClicked()));
  connect(ui->point_button, SIGNAL(clicked()), this,
          SLOT(PointButtonClicked()));
  connect(ui->open_parenthesis_button, SIGNAL(clicked()), this,
          SLOT(OpenParenthesisButtonClicked()));
  connect(ui->close_parenthesis_button, SIGNAL(clicked()), this,
          SLOT(CloseParenthesisButtonClicked()));
  connect(ui->x_button, SIGNAL(clicked()), this, SLOT(XButtonClicked()));
  connect(ui->mod_button, SIGNAL(clicked()), this, SLOT(ModButtonClicked()));
  connect(ui->pow_button, SIGNAL(clicked()), this, SLOT(PowButtonClicked()));
  connect(ui->sqrt_button, SIGNAL(clicked()), this, SLOT(SqrtButtonClicked()));
  connect(ui->e_button, SIGNAL(clicked()), this, SLOT(EButtonClicked()));
  connect(ui->backspace_button, SIGNAL(clicked()), this,
          SLOT(BackspaceClicked()));
}

View::~View() { delete ui; }

void View::ClearButtonClicked() {
  string_to_calculate.clear();
  string_to_show.clear();
  ui->display->setText("0");
  ui->x_value_input->clear();
  num_clicked = false;
  point_clicked = false;
  operator_clicked = false;
  x_clicked = false;
  open_parenthesis_clicked = 0;
  flag_first_zero = false;
  e_clicked = false;
  //  ui->plot->clearGraphs();
  //  ui->plot->replot();
  ui->expression->clear();
  GetAllFlags();
}

void View::NumberClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  if (string_to_calculate.length() != 0 && point_clicked == false &&
      string_to_calculate.back() == '0' && button->text() == '0' &&
      flag_first_zero == false) {
    flag_first_zero = false;
  }

  if (string_to_calculate.length() != 0 && point_clicked == false &&
      button->text() != '0') {
    if (string_to_calculate.back() == '0' && flag_first_zero == false) {
      string_to_calculate.chop(1);
      string_to_show.chop(1);
    }

    flag_first_zero = true;
  }

  if ((flag_first_zero == true ||
       (num_clicked == false || point_clicked == true)) &&
      button->text() != '0') {
    if (string_to_calculate.length() == 0) {
      string_to_calculate += button->text();
      string_to_show += button->text();
      ui->display->setText(string_to_show);
      num_clicked = true;
      operator_clicked = false;
      flag_first_zero = true;

    } else if (string_to_calculate.length() != 0 &&
               string_to_calculate.back() != ')' &&
               string_to_calculate.back() != 'x') {
      string_to_calculate += button->text();
      string_to_show += button->text();
      ui->display->setText(string_to_show);
      num_clicked = true;
      operator_clicked = false;
      flag_first_zero = true;
    }

  } else if ((flag_first_zero == true ||
              (num_clicked == false || point_clicked == true)) &&
             button->text() == '0') {
    if (string_to_calculate.length() == 0) {
      string_to_calculate += button->text();
      string_to_show += button->text();
      ui->display->setText(string_to_show);
      num_clicked = true;
      operator_clicked = false;

    } else if (string_to_calculate.length() != 0 &&
               string_to_calculate.back() != ')' &&
               string_to_calculate.back() != 'x') {
      string_to_calculate += button->text();
      string_to_show += button->text();
      ui->display->setText(string_to_show);
      num_clicked = true;
      operator_clicked = false;
    }
  }
  GetAllFlags();
}

void View::PlusMinusOperatorClicked() {
  if (string_to_calculate.length() != 0 && operator_clicked == false &&
      string_to_calculate.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (string_to_calculate.back() != 'e') {
      e_clicked = false;
    }

    string_to_calculate += button->text();
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    num_clicked = false;
    flag_first_zero = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;

  } else if (string_to_calculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    operator_clicked = true;
  }
  GetAllFlags();
}

void View::MulDivOperatorClicked() {
  if (operator_clicked == false && string_to_calculate.length() != 0 &&
      string_to_calculate.back() != '(' && string_to_calculate.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (button->text() == "×") {
      string_to_calculate += "*";

    } else if (button->text() == "÷") {
      string_to_calculate += "/";
    }

    string_to_show += button->text();
    ui->display->setText(string_to_show);
    num_clicked = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;
  }
  GetAllFlags();
}

void View::MathFunctionClicked() {
  bool flag = false;
  if (string_to_calculate.length() != 0) {
    if (num_clicked == false && point_clicked == false &&
        string_to_calculate.back() != 'x' &&
        string_to_calculate.back() != ')') {
      flag = true;
      QPushButton *button = qobject_cast<QPushButton *>(sender());
      string_to_calculate += button->text() + "(";
      string_to_show += button->text() + "(";
      ui->display->setText(string_to_show);
      open_parenthesis_clicked++;
      num_clicked = false;
      operator_clicked = false;
      e_clicked = false;
    }

  } else if ((operator_clicked == true || string_to_calculate.length() == 0 ||
              open_parenthesis_clicked > 0) &&
             !flag) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text() + "(";
    string_to_show += button->text() + "(";
    ui->display->setText(string_to_show);
    open_parenthesis_clicked++;
    num_clicked = false;
    operator_clicked = false;
  }
  GetAllFlags();
}

void View::OpenParenthesisButtonClicked() {
  if (string_to_calculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    open_parenthesis_clicked++;

  } else if (string_to_calculate.length() != 0 &&
             (operator_clicked == true || open_parenthesis_clicked > 0) &&
             string_to_calculate.back() != 'x' && num_clicked == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    open_parenthesis_clicked++;
    operator_clicked = false;
    num_clicked = false;
  }
  GetAllFlags();
}

void View::CloseParenthesisButtonClicked() {
  if (open_parenthesis_clicked > 0 && string_to_calculate.back() != '.' &&
      (num_clicked == true || string_to_calculate.back() == ')' ||
       x_clicked == true)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    open_parenthesis_clicked--;
    operator_clicked = false;
  }
  GetAllFlags();
}

void View::PointButtonClicked() {
  if (num_clicked == true && point_clicked == false &&
      string_to_calculate.back() != ')' && e_clicked == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    point_clicked = true;
  }
  GetAllFlags();
}

void View::ModButtonClicked() {
  if (operator_clicked == false && (num_clicked == true || x_clicked == true) &&
      string_to_calculate.back() != '.' && e_clicked == false) {
    string_to_calculate += "%";
    string_to_show += "%";
    ui->display->setText(string_to_show);
    operator_clicked = true;
    point_clicked = false;
    num_clicked = false;
    x_clicked = false;
  }
  GetAllFlags();
}

void View::PowButtonClicked() {
  if (string_to_calculate.length() != 0 && string_to_calculate.back() != '.' &&
      e_clicked == false &&
      (num_clicked == true || string_to_calculate.back() == ')' ||
       string_to_calculate.back() == 'x')) {
    string_to_calculate += "^(";
    string_to_show += "^(";
    ui->display->setText(string_to_show);
    open_parenthesis_clicked++;
    num_clicked = false;
    x_clicked = false;
  }
  GetAllFlags();
}

void View::SqrtButtonClicked() {
  if (string_to_calculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text() + "(";
    string_to_show += button->text() + "(";
    ui->display->setText(string_to_show);
    open_parenthesis_clicked++;
    operator_clicked = false;

  } else if (string_to_calculate.length() != 0 &&
             (operator_clicked == true || string_to_calculate.back() == '(')) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text() + "(";
    string_to_show += button->text() + "(";
    ui->display->setText(string_to_show);
    point_clicked = false;
    open_parenthesis_clicked++;
    operator_clicked = false;
  }
  GetAllFlags();
}

void View::XButtonClicked() {
  if ((string_to_calculate.length() == 0 || operator_clicked == true) ||
      (open_parenthesis_clicked > 0 && num_clicked == false &&
       x_clicked == false)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += "x";
    string_to_show += button->text();
    ui->display->setText(string_to_show);
    x_clicked = true;
    operator_clicked = false;
    num_clicked = false;
  }
  GetAllFlags();
}

void View::EButtonClicked() {
  if (e_clicked == false && num_clicked == true && point_clicked == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_show += button->text();
    string_to_calculate += button->text();
    ui->display->setText(string_to_show);
    e_clicked = true;
  }
  GetAllFlags();
}

void View::ChopString(size_t number_to_chop) {
  string_to_calculate.chop(number_to_chop);
  string_to_show.chop(number_to_chop);
}

void View::BackspaceClicked() {
  if (string_to_calculate.length() != 0) {
    if (string_to_calculate.length() == 1) {
      ClearButtonClicked();
      return;
    }

    QString last_five_chars = string_to_calculate.right(5);
    QString last_four_chars = string_to_calculate.right(4);
    QString last_three_chars = string_to_calculate.right(3);
    QString last_two_chars = string_to_calculate.right(2);

    if (string_to_calculate.back() == '.') {
      ChopString(1);
      point_clicked = false;

    } else if (string_to_calculate.back() == '%' ||
               string_to_calculate.back() == '+' ||
               string_to_calculate.back() == '-' ||
               string_to_calculate.back() == '*' ||
               string_to_calculate.back() == '/') {
      ChopString(1);
      QString::iterator str = string_to_calculate.end() - 1;
      point_clicked = GetPointStatus(str);
      flag_first_zero = GetZeroStatus(str);
      e_clicked = GetEStatus(str);

    } else if (string_to_calculate.back() == ')') {
      ChopString(1);
      open_parenthesis_clicked++;

    } else if (string_to_calculate.back() == 'x') {
      string_to_calculate.chop(1);
      string_to_show.chop(2);

    } else if (string_to_calculate.back() == 'e') {
      ChopString(1);
      e_clicked = false;

    } else if (last_five_chars == "acos(" || last_five_chars == "asin(" ||
               last_five_chars == "atan(") {
      ChopString(5);
      open_parenthesis_clicked--;

    } else if (last_four_chars == "cos(" || last_four_chars == "sin(" ||
               last_four_chars == "tan(" || last_four_chars == "log(") {
      ChopString(4);
      open_parenthesis_clicked--;

    } else if (last_three_chars == "ln(") {
      ChopString(3);
      open_parenthesis_clicked--;

    } else if (last_two_chars == "^(" || last_two_chars == "√(") {
      ChopString(2);
      open_parenthesis_clicked--;

    } else if (string_to_calculate.back() == '(') {
      ChopString(1);
      open_parenthesis_clicked--;

    } else { /* if number */

      ChopString(1);
    }

    QString::iterator str = string_to_calculate.end() - 1;
    num_clicked = GetNumStatus(str);
    operator_clicked = GetOperatorStatus(str);
    x_clicked = GetXStatus(str);
    ui->display->setText(string_to_show);

  } else { /* string is empty */

    ClearButtonClicked();
  }
  GetAllFlags();
}

bool View::GetPointStatus(QString::iterator str) {
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

bool View::GetOperatorStatus(QString::iterator str) {
  if (!str->isNull() &&
      (*str == '+' || *str == '-' || *str == '*' || *str == '/')) {
    return true;
  }

  return false;
}

bool View::GetZeroStatus(QString::iterator str) {
  if (!str->isNull() && *str == '0') {
    return false;
  }

  return true;
}

bool View::GetNumStatus(QString::iterator str) {
  if (!str->isNull() && str->isDigit() || *str == '.') {
    return true;
  }

  return false;
}

bool View::GetXStatus(QString::iterator str) {
  if (!str->isNull() && *str == 'x') {
    return true;
  }

  return false;
}

bool View::GetEStatus(QString::iterator str) {
  if (!str->isNull() && *str == 'e') {
    return true;
  }

  str -= 2;

  if (!str->isNull() && *str == 'e') {
    return true;
  }

  return false;
}

void View::GetAllFlags() {
  std::cout << "string: " << string_to_calculate.toStdString() << std::endl;
  std::cout << "num_clicked: " << num_clicked << std::endl;
  std::cout << "point_clicked: " << point_clicked << std::endl;
  std::cout << "operator_clicked: " << operator_clicked << std::endl;
  std::cout << "open_parenthesis_clicked: " << open_parenthesis_clicked
            << std::endl;
  std::cout << "x_clicked: " << x_clicked << std::endl;
  std::cout << "e_clicked: " << e_clicked << std::endl;
  std::cout << "flag_first_zero: " << flag_first_zero << std::endl;
}

// void View::EqualButtonClicked() {
//   if (open_parenthesis_clicked == 0 && string_to_calculate.length() != 0 &&
//       operator_clicked == false) {
//     QByteArray mainDisplay = string_to_calculate.toLocal8Bit();
//     mainData = mainDisplay.data();
//     xValue = ui->x_value_input->text().toDouble();
//     ui->expression->setText(string_to_calculate);
//     int returnCode = parse(mainData, xValue, &resultValue);
//     if (returnCode == 0) {
//       ui->display->setText("ERROR");
//       string_to_calculate.clear();
//       num_clicked = false;
//       point_clicked = false;
//       operator_clicked = false;
//       x_clicked = false;
//       open_parenthesis_clicked = 0;
//     } else {
//       check_result(resultValue, result_string);
//       ui->display->setText(result_string);
//       string_to_calculate.clear();
//       num_clicked = false;
//       point_clicked = false;
//       operator_clicked = false;
//       x_clicked = false;
//       open_parenthesis_clicked = 0;
//     }
//   }
// }
