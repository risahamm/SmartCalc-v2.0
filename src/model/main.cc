#include <iostream>

#include "calculation.h"
#include "format_string.h"
#include "reverse_polish_notation.h"
using namespace std;

int main() {

  wstring str = L"(2+3)×cos(100-100)";
//  wstring str = L"2^(2^(3))";

  s21::FormatString a(str);

  s21::ReversePolishNotation b(a.GetString());

  s21::Calculation c(b.GetRpnList());

  cout << "end " << c.GetResult() << endl;


}

