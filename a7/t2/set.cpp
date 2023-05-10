#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "set.hpp"

Set::Set() : nums({}) {}

Set Set::operator+(const Set &other) const {
  Set set = *this;
  for(int n : other.nums)
    set+=n;
  return set;
}

Set &Set::operator+=(const int &num){
  if(std::find(nums.begin(), nums.end(), num) == nums.end())
    nums.push_back(num);
  return *this;
}

Set &Set::operator=(const Set &other){
  nums = other.nums;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Set &set){
  int size = set.nums.size();
  os << '{';
  for(int i = 0; i < size-1; i++)
    os << set.nums[i] << ", ";
  if(size > 0)
    os << set.nums[size-1];
  os << '}';
  return os;
}