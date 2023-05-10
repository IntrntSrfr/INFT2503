#pragma once
#include <vector>
#include <iostream>

class Set {
 public:
  Set();

  Set operator+(const Set &other) const; // union
  Set &operator+=(const int &num); // add number
  Set &operator=(const Set &other); // set equal to another Set

  friend std::ostream &operator<<(std::ostream &os, const Set &set);

 private:
  std::vector<int> nums;
};