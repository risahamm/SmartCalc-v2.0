#include <iostream>

#include "calculation.h"
#include "format_string.h"
#include "reverse_polish_notation.h"
using namespace std;

int main() {

//  wstring str = L"(2+3)×cos(100-100)";
  wstring str = L"X+1+1e-2";

  s21::FormatString a(str);

  s21::ReversePolishNotation b(a.GetString());

  s21::Calculation c(b.GetRpnList(), 2);

  cout << "end " << c.GetResult() << endl;

//string str = "e";
//double x = 0;
//x = std::stod(str);
//cout << "x = " << x << endl;


}

