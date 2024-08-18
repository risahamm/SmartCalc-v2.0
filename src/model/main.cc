#include <iostream>

#include "wide_string_to_basic.h"
using namespace std;

int main() {
  //    s21::ReversePolishNotation a("12+(-1)");

  setlocale(LC_ALL, "rus");

  wstring str;
  str = L"1×2÷3+√(25.0)-ln(3)-log(2)+asin(1)-tan(0)";

  s21::WideStringToBasic a(str);

  cout << "end " << endl;




}

