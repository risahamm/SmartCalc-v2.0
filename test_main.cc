#include <iostream>
#include <map>

//#include "calculation.h"
//#include "reverse_polish_notation.h"
#include "src/controller/controller.h"

using namespace std;

int main() {
//  s21::Calculation c;
//  std::string str = "3.5+4*s(3.14/2)-5/2";
//  //  c.Parse(str, 0);
//  //  cout << "end " << c.GetResult() << endl;
//
//  s21::Controller a(&c);

//cout << "res = " << a.Calculate(str, -1.5) << endl;
//printf("res = %.7Lf\n", a.Calculate(str, -1.5));

  std::string str = "2e-66666";
  long double res = std::stold(str);
  cout << res << endl;

  cout << "end " << endl;
}
