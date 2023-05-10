#include "set.hpp"
#include <iostream>
#include <string>

int main() {
  Set s1;
  std::cout << "empty set" << '\n';
  std::cout << "set 1:" << s1 << '\n';
  s1+=5;
  s1+=3;
  s1+=5;
  std::cout << "adding [5,3,5] to the first set" << "\n";
  std::cout << "set 1:" << s1 << "\n\n";

  Set s2;
  s2 += 5;
  s2 += 6;
  std::cout << "adding [5, 6] to the second set" << "\n";
  std::cout << "set 2:" << s2 << "\n\n";

  Set s3 = s1+s2;
  std::cout << "first set + second set (should contain {3,5,6}):" << '\n';
  std::cout << "set 3:" << s3 << "\n\n";

  std::cout << "setting set 3 to set 1" << '\n';
  std::cout << "set 3 before:" << s3 << '\n';
  s3 = s1;
  std::cout << "set 3 after:" << s3 << '\n';

}
