#include "view.h"

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
                     SLOT(numberClicked()));
  }

  std::vector<QPushButton *> plus_minus_operators = {ui->minus_button,
                                                     ui->plus_button};
  for (QPushButton *op_button : plus_minus_operators) {
    QObject::connect(op_button, SIGNAL(clicked()), this,
                     SLOT(plusMinusOperatorClicked()));
  }

  std::vector<QPushButton *> mul_div_operators = {ui->multiply_button,
                                                  ui->divide_button};
  for (QPushButton *mul_div_op_button : mul_div_operators) {
    QObject::connect(mul_div_op_button, SIGNAL(clicked()), this,
                     SLOT(mulDivOperatorClicked()));
  }

  std::vector<QPushButton *> math_functions = {
      ui->tan_button,  ui->cos_button,  ui->sin_button, ui->atan_button,
      ui->acos_button, ui->asin_button, ui->log_button, ui->ln_button};
  for (QPushButton *function_button : math_functions) {
    QObject::connect(function_button, SIGNAL(clicked()), this,
                     SLOT(mathFunctionClicked()));
  }

  connect(ui->clear_button, SIGNAL(clicked()), this,
          SLOT(clearButtonClicked()));
  connect(ui->point_button, SIGNAL(clicked()), this,
          SLOT(pointButtonClicked()));
  connect(ui->open_parenthesis_button, SIGNAL(clicked()), this,
          SLOT(openParenthesisButtonClicked()));
  connect(ui->close_parenthesis_button, SIGNAL(clicked()), this,
          SLOT(closeParenthesisButtonClicked()));
  connect(ui->x_button, SIGNAL(clicked()), this, SLOT(xButtonClicked()));
  connect(ui->mod_button, SIGNAL(clicked()), this, SLOT(modButtonClicked()));
  connect(ui->pow_button, SIGNAL(clicked()), this, SLOT(powButtonClicked()));
  connect(ui->sqrt_button, SIGNAL(clicked()), this, SLOT(sqrtButtonClicked()));
}

View::~View() { delete ui; }

void View::clearButtonClicked() {
  stringToCalculate.clear();
  ui->display->setText("0");
  ui->x_value_input->clear();
  num_clicked = false;
  point_clicked = false;
  operator_clicked = false;
  x_clicked = false;
  open_parenthesis_clicked = 0;
  flag_first_zero = false;
  //  ui->plot->clearGraphs();
  //  ui->plot->replot();
  ui->expression->clear();
}

void View::numberClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  if (stringToCalculate.length() != 0 && point_clicked == false &&
      stringToCalculate.back() == '0' && button->text() == '0' &&
      flag_first_zero == false) {
    flag_first_zero = false;
  }
  if (stringToCalculate.length() != 0 && point_clicked == false &&
      button->text() != '0') {
    if (stringToCalculate.back() == '0' && flag_first_zero == false) {
      stringToCalculate.chop(1);
    }
    flag_first_zero = true;
  }
  if ((flag_first_zero == true ||
       (num_clicked == false || point_clicked == true)) &&
      button->text() != '0') {
    if (stringToCalculate.length() == 0) {
      stringToCalculate += button->text();
      ui->display->setText(stringToCalculate);
      num_clicked = true;
      operator_clicked = false;
      flag_first_zero = true;
    } else if (stringToCalculate.length() != 0 &&
               stringToCalculate.back() != ')' &&
               stringToCalculate.back() != 'X') {
      stringToCalculate += button->text();
      ui->display->setText(stringToCalculate);
      num_clicked = true;
      operator_clicked = false;
      flag_first_zero = true;
    }
  } else if ((flag_first_zero == true ||
              (num_clicked == false || point_clicked == true)) &&
             button->text() == '0') {
    if (stringToCalculate.length() == 0) {
      stringToCalculate += button->text();
      ui->display->setText(stringToCalculate);
      num_clicked = true;
      operator_clicked = false;
    } else if (stringToCalculate.length() != 0 &&
               stringToCalculate.back() != ')' &&
               stringToCalculate.back() != 'X') {
      stringToCalculate += button->text();
      ui->display->setText(stringToCalculate);
      num_clicked = true;
      operator_clicked = false;
    }
  }
}

void View::plusMinusOperatorClicked() {
  if (stringToCalculate.length() != 0 && operator_clicked == false &&
      stringToCalculate.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    num_clicked = false;
    flag_first_zero = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;
  } else if (stringToCalculate.length() == 0 && operator_clicked == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    num_clicked = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;
  }
}

void View::mulDivOperatorClicked() {
  if (operator_clicked == false && stringToCalculate.length() != 0 &&
      stringToCalculate.back() != '(' && stringToCalculate.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    num_clicked = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;
  }
}

void View::mathFunctionClicked() {
  bool flag = false;
  if (stringToCalculate.length() != 0) {
    if (num_clicked == false && point_clicked == false &&
        stringToCalculate.back() != 'x' && stringToCalculate.back() != ')') {
      flag = true;
      QPushButton *button = qobject_cast<QPushButton *>(sender());
      stringToCalculate += button->text() + "(";
      ui->display->setText(stringToCalculate);
      open_parenthesis_clicked++;
      num_clicked = false;
      operator_clicked = false;
    }
  } else if ((operator_clicked == true || stringToCalculate.length() == 0 ||
              open_parenthesis_clicked > 0) &&
             !flag) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text() + "(";
    ui->display->setText(stringToCalculate);
    open_parenthesis_clicked++;
    num_clicked = false;
    operator_clicked = false;
  }
}

void View::openParenthesisButtonClicked() {
  if (stringToCalculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    open_parenthesis_clicked++;
  } else if (stringToCalculate.length() != 0 &&
             (operator_clicked == true || open_parenthesis_clicked > 0) &&
             stringToCalculate.back() != 'x' && num_clicked == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    open_parenthesis_clicked++;
    operator_clicked = false;
    num_clicked = false;
  }
}

void View::closeParenthesisButtonClicked() {
  if (open_parenthesis_clicked > 0 && stringToCalculate.back() != '.' &&
      (num_clicked == true || stringToCalculate.back() == ')' ||
       x_clicked == true)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    open_parenthesis_clicked--;
    operator_clicked = false;
  }
}

void View::pointButtonClicked() {
  if (num_clicked == true && point_clicked == false &&
      stringToCalculate.back() != ')') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    point_clicked = true;
  }
}

void View::modButtonClicked() {
  if (operator_clicked == false && (num_clicked == true || x_clicked == true) &&
      stringToCalculate.back() != '.') {
    stringToCalculate += "%";
    ui->display->setText(stringToCalculate);
    operator_clicked = true;
    point_clicked = false;
    num_clicked = false;
    x_clicked = false;
  }
}

void View::powButtonClicked() {
  if (stringToCalculate.length() != 0 && stringToCalculate.back() != '.' &&
      (num_clicked == true || stringToCalculate.back() == ')' ||
       stringToCalculate.back() == 'X')) {
    stringToCalculate += "^(";
    ui->display->setText(stringToCalculate);
    open_parenthesis_clicked++;
    num_clicked = false;
    x_clicked = false;
  }
}

void View::sqrtButtonClicked() {
  if (stringToCalculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text() + "(";
    ui->display->setText(stringToCalculate);
    open_parenthesis_clicked++;
    operator_clicked = false;
  } else if (stringToCalculate.length() != 0 &&
             (operator_clicked == true || stringToCalculate.back() == '(')) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text() + "(";
    ui->display->setText(stringToCalculate);
    point_clicked = false;
    open_parenthesis_clicked++;
    operator_clicked = false;
  }
}

void View::xButtonClicked() {
  if ((stringToCalculate.length() == 0 || operator_clicked == true) ||
      (open_parenthesis_clicked > 0 && num_clicked == false &&
       x_clicked == false)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    stringToCalculate += button->text();
    ui->display->setText(stringToCalculate);
    x_clicked = true;
    operator_clicked = false;
    num_clicked = false;
  }
}

// void View::on_equal_button_clicked() {
//   if (open_parenthesis_clicked == 0 && stringToCalculate.length() != 0 &&
//       operator_clicked == false) {
//     QByteArray mainDisplay = stringToCalculate.toLocal8Bit();
//     mainData = mainDisplay.data();
//     xValue = ui->x_value_input->text().toDouble();
//     ui->expression->setText(stringToCalculate);
//     int returnCode = parse(mainData, xValue, &resultValue);
//     if (returnCode == 0) {
//       ui->display->setText("ERROR");
//       stringToCalculate.clear();
//       num_clicked = false;
//       point_clicked = false;
//       operator_clicked = false;
//       x_clicked = false;
//       open_parenthesis_clicked = 0;
//     } else {
//       check_result(resultValue, result_string);
//       ui->display->setText(result_string);
//       stringToCalculate.clear();
//       num_clicked = false;
//       point_clicked = false;
//       operator_clicked = false;
//       x_clicked = false;
//       open_parenthesis_clicked = 0;
//     }
//   }
// }
