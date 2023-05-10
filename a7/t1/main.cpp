#include "fraction.hpp"
#include <iostream>
#include <string>

int main() {
  Fraction f1(10, 20);
  Fraction f2(3, 4);

  std::cout << f1 - f2 << std::endl;
  std::cout << f2 - 5 << std::endl;
  std::cout << 5 - f2 << std::endl;
}

// output:
// -1/4
// -17/4
// 17/4

// b:
// 5 - 3 - fraction1 - 7 - fraction2
// this will be expanded as following
// ((((5 - 3) - fraction1) - 7) - fraction2)

// 5-3 will use builtin integer operator- and return an integer 2.
// (2 - fraction1) will use Fraction operator-(int num, const Fraction &other), because the first operand is not of Fraction class and will return a Fraction object.
// (2 - fraction1) - 7 will use Fraction operator-(const int &other), since the first operand is of Fraction class, and return a Fraction object.
// the final calculation will use Fraction operator-(const Fraction &other), since both the operands are Fraction objects at this point.