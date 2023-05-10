#include <fstream>
#include <iostream>
#include <string>

void read_temperatures(double temperatures[], int length);

int main() {
  const int length = 5;
  double temps[length];
  int low, mid, high;
  low = mid = high = 0;

  read_temperatures(temps, length);
  for (double c : temps) {
    if (c > 20) high++;
    else if (c > 9) mid++;
    else low++;
  }

  std::cout << "Temps below 10: " << low << std::endl;
  std::cout << "Temps between 10 and 20: " << mid << std::endl;
  std::cout << "Temps above 20: " << high << std::endl;
  return 0;
}

void read_temperatures(double temperatures[], int length) {
  std::fstream file("list");
  if (!file.is_open()) {
    std::cerr << "could not open file" << std::endl;
    return;
  }

  for (int i = 0; i < length; i++)
    file >> temperatures[i];

  file.close();
}
