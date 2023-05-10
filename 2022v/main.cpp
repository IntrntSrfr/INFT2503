#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

void t1();
void t2_a();
void t2_b();
void t3();
void t4();

int main() {
  t1();
  t2_a();
  t2_b();
  t4();
  t3();
  return 0;
}

int times_two(int num) { return num * 2; };
double times_two(double num) { return num * 2; };
std::string times_two(std::string str) { return str + str; };
std::vector<int> times_two(std::vector<int> vec) {
  std::vector<int> res;
  for (auto &v : vec)
    res.push_back(v * 2);
  return res;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec) {
  int size = vec.size();
  os << '{';
  for (int i = 0; i < size - 1; i++)
    os << vec[i] << ", ";
  if (size > 0)
    os << vec[size - 1];
  os << '}';
  return os;
};

void t1() {
  std::cout << times_two(2) << std::endl;
  std::cout << times_two(2.25) << std::endl;
  std::cout << times_two("test") << std::endl;
  std::cout << times_two(std::vector<int>{1, 2, 3}) << std::endl;
};

class Build {
public:
  virtual std::string build() const = 0;
};
class CMake : public Build {
public:
  std::string build() const override { return "cmake --build ."; };
};
class Meson : public Build {
public:
  std::string build() const override { return "meson compile -C ."; };
};
class Cargo : public Build {
public:
  std::string build() const override { return "cargo build"; };
};

class ProgrammingLanguage {
public:
  std::unique_ptr<Build> build_config;

  ProgrammingLanguage(){};
  ProgrammingLanguage(std::unique_ptr<Build> build_)
      : build_config(std::move(build_)){};

  virtual std::string print_line(std::string message) const = 0;
  virtual std::string for_each(std::string variable,
                               std::string source) const = 0;
  std::string build() const { return build_config->build(); };
};

class Cpp : public ProgrammingLanguage {
public:
  Cpp(){};
  Cpp(std::unique_ptr<Build> build) : ProgrammingLanguage(std::move(build)){};

  std::string print_line(std::string message) const override {
    return "cout << \"" + message + "\" << endl;";
  };
  std::string for_each(std::string variable,
                       std::string source) const override {
    return "for(auto &" + variable + ": " + source + ") {}";
  };
};

class Rust : public ProgrammingLanguage {
public:
  Rust(){};
  Rust(std::unique_ptr<Build> build) : ProgrammingLanguage(std::move(build)){};

  std::string print_line(std::string message) const override {
    return "println!(\"" + message + "\");";
  };
  std::string for_each(std::string variable,
                       std::string source) const override {
    return "for " + variable + " in &" + source + " {}";
  };
};

void t2_a() {
  std::vector<std::unique_ptr<ProgrammingLanguage>> programming_languages;

  // programming_languages.emplace_back(std::make_unique<ProgrammingLanguage>());
  programming_languages.emplace_back(std::make_unique<Cpp>());
  programming_languages.emplace_back(std::make_unique<Rust>());

  for (auto &programming_language : programming_languages) {
    std::cout << programming_language->print_line("Hello World") << std::endl;
    std::cout << programming_language->for_each("e", "vec") << std::endl
              << std::endl;
  }
};

void t2_b() {
  std::vector<std::unique_ptr<ProgrammingLanguage>> programming_languages;
  programming_languages.emplace_back(
      std::make_unique<Cpp>(std::make_unique<CMake>()));
  programming_languages.emplace_back(
      std::make_unique<Cpp>(std::make_unique<Meson>()));
  programming_languages.emplace_back(
      std::make_unique<Rust>(std::make_unique<Cargo>()));

  for (auto &programming_language : programming_languages) {
    std::cout << programming_language->build() << std::endl;
  }
};

template <typename T1> class Angle {
public:
  Angle(int value_) : value(value_ % 360){};
  Angle(double value_) : value(fmod(value_, 3.14159265359)){};

  T1 value;

  template <typename T2> Angle<T1> operator+(const T2 other) {
    return Angle<T1>(value + static_cast<T1>(other));
  };

  friend std::ostream &operator<<(std::ostream &os, const Angle<T1> &angle) {
    return os << angle.value;
  };
};

void t3() {
  std::cout << Angle<int>(30) << std::endl;
  std::cout << (Angle<int>(30) + 360) << std::endl;
  std::cout << (Angle<int>(30) + 3.14159265359) << std::endl;
  std::cout << Angle<double>(3.14159265359 / 2) << std::endl;
  std::cout << (Angle<double>(3.14159265359 / 2) + 3.14159265359) << std::endl;
  std::cout << (Angle<double>(3.14159265359 / 2) + 3) << std::endl;
};

std::vector<int>
parallell_transform(std::vector<int> a, std::vector<int> b,
                    const std::function<int(int, int)> &lambda) {
  int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  threads.reserve(num_threads);

  std::vector<int> res(a.size());

  for (int i = 0; i < num_threads; i++) {
    threads.emplace_back([i, num_threads, &res, &a, &b, &lambda] {
      for (int j = i; j < a.size() && j < b.size(); j += num_threads)
        res[j] = lambda(a[j], b[j]);
    });
  }

  for (auto &thread : threads)
    thread.join();
  return res;
};

void t4() {
  std::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {2, 3, 4, 5, 6};

  std::cout << parallell_transform(a, b, [](int a_element, int b_element) {
    return a_element + b_element;
  }) << std::endl;

  std::cout << parallell_transform(a, b, [](int a_element, int b_element) {
    return a_element * b_element;
  }) << std::endl;
};