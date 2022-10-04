#include <vector>
#include <iostream>
#include <algorithm>

int main(){
  std::vector<double> v = {2,4,6,8,10};
  std::cout << v.front() << ", " << v.back() << '\n';
  
  v.emplace(v.begin()+1, 100);
  std::cout << v.front() << '\n';

  std::vector<double>::iterator it = std::find(v.begin(), v.end(), 4);
  if(it != v.end())
    std::cout << "number found in v: " << *it << '\n';
  else
    std::cout << "number was not found\n";

  return 0;
}
