#include <iostream>
#include <iomanip>

template <typename T>
bool equal(T a, T b);
bool equal(double a, double b);

int main(){
  int a = 1;
  int b = 2;
  std::cout << std::fixed << a << " == " << b << ": " << (equal(a, b) ? "true" : "false") << ", should be false" << '\n';
  std::cout << std::fixed << a << " == " << a << ": " << (equal(a, a) ? "true" : "false") << ", should be true" << '\n';

  double c = 0.0000003;
  double d = 0.0000004;
  double e = 0.3;
  std::cout << std::fixed << std::setprecision(7) << c << " == " << d << ": " << (equal(c, d) ? "true" : "false") << ", should be true" << '\n';
  std::cout << std::fixed << std::setprecision(7) << c << " == " << e << ": " << (equal(c, e) ? "true" : "false") << ", should be false" << '\n';
  
  return 0;
}

template <typename T>
bool equal(T a, T b){
  std::cout << "calling template" << '\n';
  return a == b;
}

bool equal(double a, double b){
  std::cout << "calling double" << '\n';
  double threshold = 0.0001;
  return std::abs(a-b) < threshold;
}
