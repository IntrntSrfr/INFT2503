#include <functional>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void t1();
void t2();
void t3();
void t4();

int main() {
  t1();
  t2();
  t3();
  t4();
  return 0;
}

string concat(string s1, string s2) { return s1 + s2; };
string concat(int n1, int n2) { return to_string(n1) + to_string(n2); };
string concat(vector<string> vec) {
  string res = "";
  for (auto &c : vec)
    res += c;
  return res;
};

void t1() {
  cout << concat("hello", "world") << endl;
  cout << concat(1, 2) << endl;
  cout << concat({"a", "b", "c"}) << endl;
};

class Animal {
public:
  virtual ~Animal(){};
  virtual string makeNoise() const = 0;
};

class Pig : public Animal {
public:
  string makeNoise() const override { return "Honk!"; }
};

class Elephant : public Animal {
public:
  string makeNoise() const override { return "Toot!"; }
};

void t2() {
  vector<unique_ptr<Animal>> animals;
  animals.emplace_back(make_unique<Elephant>());
  animals.emplace_back(make_unique<Elephant>());
  animals.emplace_back(make_unique<Pig>());

  for (auto &a : animals)
    cout << a->makeNoise() << endl;
};

template <typename T1>
std::ostream &operator<<(std::ostream &os, const std::vector<T1> &vec) {
  int size = vec.size();
  os << "{ ";
  for (int i = 0; i < size - 1; i++)
    os << vec[i] << ", ";
  if (size > 0)
    os << vec[size - 1];
  os << " }";
  return os;
};

template <typename T1, typename T2>
vector<T2> map_f(const vector<T1> &vec, const function<T2(T1)> &lambda) {
  vector<T2> res(vec.size());
  for (int i = 0; i < vec.size(); i++)
    res[i] = lambda(vec[i]);
  return res;
};

void t3() {
  cout << map_f<int, int>({1, 2, 3}, [](int a) { return a * 2; }) << endl;
  cout << map_f<float, float>({1, 2.3, 3}, [](float a) { return a / 2; })
       << endl;
  cout << map_f<string, string>({"hello", "world"}, [](string s) {
    return s + ".";
  }) << endl;
  cout << map_f<string, int>({"hello", "world"}, [](string s) {
    return s.size();
  }) << endl;
};

template <typename T1> class Matrix {
public:
  Matrix(vector<vector<T1>> values_) : values(values_){};
  vector<vector<T1>> values;

  // i have made the assumption that this is specialized for this task.
  // that means this is not generalized, and only works for the MxN * NxM
  // matrices given.
  friend Matrix operator*(const Matrix<T1> &self, const Matrix<T1> &other) {
    int size = self.values.size(); // res matrix size = thread amt
    int other_size =
        other.values.size(); // multiplications for each value in result matrix

    vector<thread> threads;
    threads.reserve(size);

    // initialize result matrix
    vector<vector<T1>> res(size, vector<T1>(size, 0));

    for (int i = 0; i < size; i++) {
      threads.emplace_back([i, size, other_size, &res, &self, &other] {
        for (int j = 0; j < size; j++) {
          for (int k = 0; k < other_size; k++) {
            res[i][j] += self.values[i][k] * other.values[k][j];
          }
        }
      });
    };

    for (auto &thread : threads)
      thread.join();
    return res;
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    for (auto &row : mat.values) {
      int rl = row.size();
      os << "[ ";
      for (int i = 0; i < rl - 1; i++)
        os << row[i] << ' ';
      if (rl > 0)
        os << row[rl - 1];
      os << " ]\n";
    };
    return os;
  };
};

void t4() {
  Matrix<int> m_a({{1, 2}, {3, 4}, {5, 6}});
  Matrix<int> m_b({{1, 2, 3}, {4, 5, 6}});

  cout << m_a << endl;
  cout << m_b << endl;
  cout << m_a * m_b << endl;
  cout << m_b * m_a << endl;

  Matrix<int> m_c({{1, 2}});
  Matrix<int> m_d({{2}, {2}});

  cout << m_c * m_d << endl;
  cout << m_d * m_c << endl;
};