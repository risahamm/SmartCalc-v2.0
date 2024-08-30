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
}

View::~View() { delete ui; }

void View::ClearButtonClicked() {
  string_to_calculate.clear();
  expression_string.clear();
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
      expression_string.chop(1);
    }
    flag_first_zero = true;
  }
  if ((flag_first_zero == true ||
       (num_clicked == false || point_clicked == true)) &&
      button->text() != '0') {
    if (string_to_calculate.length() == 0) {
      string_to_calculate += button->text();
      expression_string += button->text();
//      ui->display->setText(string_to_calculate);
      ui->display->setText(expression_string);
      num_clicked = true;
      operator_clicked = false;
      flag_first_zero = true;
    } else if (string_to_calculate.length() != 0 &&
               string_to_calculate.back() != ')' &&
               string_to_calculate.back() != 'x') {
      string_to_calculate += button->text();
      expression_string += button->text();
//      ui->display->setText(string_to_calculate);
      ui->display->setText(expression_string);
      num_clicked = true;
      operator_clicked = false;
      flag_first_zero = true;
    }
  } else if ((flag_first_zero == true ||
              (num_clicked == false || point_clicked == true)) &&
             button->text() == '0') {
    if (string_to_calculate.length() == 0) {
      string_to_calculate += button->text();
      expression_string += button->text();
//      ui->display->setText(string_to_calculate);
      ui->display->setText(expression_string);
      num_clicked = true;
      operator_clicked = false;
    } else if (string_to_calculate.length() != 0 &&
               string_to_calculate.back() != ')' &&
               string_to_calculate.back() != 'x') {
      string_to_calculate += button->text();
      expression_string += button->text();
//      ui->display->setText(string_to_calculate);
      ui->display->setText(expression_string);
      num_clicked = true;
      operator_clicked = false;
    }
  }
}

void View::PlusMinusOperatorClicked() {
  if (string_to_calculate.length() != 0 && operator_clicked == false &&
      string_to_calculate.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (string_to_calculate.back() != 'e') {
        e_clicked = false;
    }
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    num_clicked = false;
    flag_first_zero = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;
  } else if (string_to_calculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    operator_clicked = true;
  }
}

void View::MulDivOperatorClicked() {
  if (operator_clicked == false && string_to_calculate.length() != 0 &&
      string_to_calculate.back() != '(' && string_to_calculate.back() != '.') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    num_clicked = false;
    point_clicked = false;
    operator_clicked = true;
    x_clicked = false;
  }
}

void View::MathFunctionClicked() {
  bool flag = false;
  if (string_to_calculate.length() != 0) {
    if (num_clicked == false && point_clicked == false &&
        string_to_calculate.back() != 'x' && string_to_calculate.back() != ')') {
      flag = true;
      QPushButton *button = qobject_cast<QPushButton *>(sender());
      string_to_calculate += button->text() + "(";
      expression_string += button->text() + "(";
//      ui->display->setText(string_to_calculate);
      ui->display->setText(expression_string);
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
    expression_string += button->text() + "(";
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    open_parenthesis_clicked++;
    num_clicked = false;
    operator_clicked = false;
  }
}

void View::OpenParenthesisButtonClicked() {
  if (string_to_calculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    open_parenthesis_clicked++;
  } else if (string_to_calculate.length() != 0 &&
             (operator_clicked == true || open_parenthesis_clicked > 0) &&
             string_to_calculate.back() != 'x' && num_clicked == false) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    open_parenthesis_clicked++;
    operator_clicked = false;
    num_clicked = false;
  }
}

void View::CloseParenthesisButtonClicked() {
  if (open_parenthesis_clicked > 0 && string_to_calculate.back() != '.' &&
      (num_clicked == true || string_to_calculate.back() == ')' ||
       x_clicked == true)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    open_parenthesis_clicked--;
    operator_clicked = false;
  }
}

void View::PointButtonClicked() {
  if (num_clicked == true && point_clicked == false &&
      string_to_calculate.back() != ')') {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text();
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    point_clicked = true;
  }
}

void View::ModButtonClicked() {
  if (operator_clicked == false && (num_clicked == true || x_clicked == true) &&
      string_to_calculate.back() != '.') {
    string_to_calculate += "%";
    expression_string += "%";
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    operator_clicked = true;
    point_clicked = false;
    num_clicked = false;
    x_clicked = false;
  }
}

void View::PowButtonClicked() {
  if (string_to_calculate.length() != 0 && string_to_calculate.back() != '.' &&
      (num_clicked == true || string_to_calculate.back() == ')' ||
       string_to_calculate.back() == 'x')) {
    string_to_calculate += "^(";
    expression_string += "^(";
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    open_parenthesis_clicked++;
    num_clicked = false;
    x_clicked = false;
  }
}

void View::SqrtButtonClicked() {
  if (string_to_calculate.length() == 0) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text() + "(";
    expression_string += button->text() + "(";
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    open_parenthesis_clicked++;
    operator_clicked = false;
  } else if (string_to_calculate.length() != 0 &&
             (operator_clicked == true || string_to_calculate.back() == '(')) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += button->text() + "(";
    expression_string += button->text() + "(";
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    point_clicked = false;
    open_parenthesis_clicked++;
    operator_clicked = false;
  }
}

void View::XButtonClicked() {
  if ((string_to_calculate.length() == 0 || operator_clicked == true) ||
      (open_parenthesis_clicked > 0 && num_clicked == false &&
       x_clicked == false)) {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    string_to_calculate += "x";
    expression_string += button->text();
//    ui->display->setText(string_to_calculate);
    ui->display->setText(expression_string);
    x_clicked = true;
    operator_clicked = false;
    num_clicked = false;
  }
}

void View::EButtonClicked() {
    if (e_clicked == false && num_clicked == true) {
        QPushButton *button = qobject_cast<QPushButton *>(sender());
        expression_string += button->text();
        string_to_calculate += button->text();
        ui->display->setText(expression_string);
        e_clicked = true;
    }
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
