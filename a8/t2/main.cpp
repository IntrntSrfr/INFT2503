#include <iostream>
#include <typeinfo>

#include "pair.hpp"

int main() {

  Pair<double, int> p1(3.5, 14);
  Pair<double, int> p2(2.1, 7);
  std::cout << "p1: " << p1.first << ", " << p1.second << std::endl;
  std::cout << "p2: " << p2.first << ", " << p2.second << std::endl;
  if (p1 > p2)
    std::cout << "p1 er størst" << std::endl;
  else
    std::cout << "p2 er størst" << std::endl;

  auto sum = p1 + p2;
  std::cout << "Sum: " << sum.first << ", " << sum.second << std::endl;

  return 0;
}