#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::ostream &operator<<(std::ostream &out, const std::vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

int main(){
  std::vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};
  std::cout << "v1: " << v1 << '\n';

  std::vector<int> v2 = {2, 3, 12, 14, 24};
  std::cout << "v2: " << v2 << '\n';

  // a)
  std::vector<int>::iterator it = std::find_if(v1.begin(), v1.end(), [](int n){return n > 15;});
  if(it != v1.end())
    std::cout << "first element above 15: v1[" << it - v1.begin() << "] = " << *it << '\n';

  // b)
  std::cout << "[v1.begin(), v1.begin() + 5> and v2 are ";
  (std::equal(v1.begin(), v1.begin() + 5, v2.begin(), [](int i, int j){return std::abs(i-j) < 3;}))
    ? std::cout << "equal" << '\n'
    : std::cout << "not equal" << '\n';
    
  std::cout << "[v1.begin(), v1.begin() + 4> and v2 are ";
  (std::equal(v1.begin(), v1.begin() + 4, v2.begin(), [](int i, int j){return std::abs(i-j) < 3;}))
    ? std::cout << "equal" << '\n'
    : std::cout << "not equal" << '\n';
  
  // c)
  std::vector<int> copy;
  copy.resize(v1.size());
  std::replace_copy_if(v1.begin(), v1.end(), copy.begin(), [](int n){return n%2==1;}, 100);
  std::cout << copy << '\n';

  return 0;
}
