#include <iostream>
#include <map>

#include "calculation.h"
#include "reverse_polish_notation.h"
using namespace std;

int main() {
//
//
  s21::Calculation c;
//
  std::string str = "9-3.3+9e*3";
//
  c.Parse(str, 0);
//
//
//
  cout << "end " << c.GetResult() << endl;
//
////string str = "6e2";
////double x = 0;
////x = std::stod(str);
////cout << "x = " << x << endl;
//
//
}

