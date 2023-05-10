
template <typename T1, typename T2>
class Pair {
 public:
  T1 first;
  T2 second;

  Pair(T1 f, T2 s) : first(f), second(s) {};

  Pair operator+(const Pair &other) const {
    Pair pair = *this;
    pair.first += other.first;
    pair.second += other.second;
    return pair;
  };

  bool operator>(const Pair &other) const {
    return (first + second > other.first + other.second);
  };
};