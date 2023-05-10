#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

void t1();
void t2();
void t3();
void t4();
// void t5();

int main() {
  t1();
  t2();
  t3();
  t4();
  // t5();
  return 0;
}

bool starts_with(std::string str, std::string substr) {
  return str.rfind(substr, 0) == 0;
};

void t1() {
  std::cout << starts_with("", "") << std::endl;
  std::cout << starts_with(std::string(""), "") << std::endl;
  std::cout << starts_with("This is a test", "This") << std::endl;
  std::cout << starts_with(std::string("This is a test"), "This") << std::endl;
  std::cout << starts_with("This is a test", "Test") << std::endl;
  std::cout << starts_with(std::string("This is a test"), "Test") << std::endl;
  std::cout << starts_with("This", "This is a test") << std::endl;
  std::cout << starts_with(std::string("This"), "This is a test") << std::endl;
};

class Animal {
public:
  virtual ~Animal(){};
  virtual std::string produce() const = 0;
};

class Chicken : public Animal {
public:
  std::string produce() const override { return "egg"; };
};
class Cow : public Animal {
public:
  std::string produce() const override { return "milk"; };
};
class Sheep : public Animal {
public:
  std::string produce() const override { return "wool"; };
};

class Farm {
public:
  Farm(){};
  std::vector<std::unique_ptr<Animal>> animals;

  void add_animal(std::string animal) {
    if (animal == "chicken")
      animals.push_back(std::make_unique<Chicken>());
    else if (animal == "cow")
      animals.push_back(std::make_unique<Cow>());
    else if (animal == "sheep")
      animals.push_back(std::make_unique<Sheep>());
  }
};

void t2() {
  Farm farm;
  farm.add_animal("chicken");
  farm.add_animal("chicken");
  farm.add_animal("chicken");
  farm.add_animal("cow");
  farm.add_animal("sheep");
  farm.add_animal("sheep");

  std::cout << "Farm production: " << std::endl;
  for (auto &animal : farm.animals)
    std::cout << animal->produce() << std::endl;
};

class Chess {
public:
  enum class Player { white, black };
  static std::string player_name(Player player) {
    return player == Player::white ? "white" : "black";
  }

  std::vector<std::function<void(Player winner)>> on_victory;

  /// In this game, black always wins
  void play() {
    for (auto &event : on_victory) {
      event(Player::black);
    }
  }
};

void t3() {
  Chess chess;

  chess.on_victory.emplace_back([](Chess::Player winner) {
    std::cout << Chess::player_name(winner) << " won" << std::endl;
  });

  chess.on_victory.emplace_back([](Chess::Player winner) {
    std::cout << Chess::player_name(winner == Chess::Player::white
                                        ? Chess::Player::black
                                        : Chess::Player::white)
              << " lost" << std::endl;
  });
  chess.play();
};

class Meter {
public:
  const static int multiplier = 1;
};
class Kilometer {
public:
  const static int multiplier = 1000;
};

template <class T1> class Distance {
public:
  Distance(int units_) : meters(units_ * T1::multiplier){};

  int meters;

  Distance &operator+=(const int units) {
    meters += units * T1::multiplier;
    return *this;
  };

  Distance operator+(const Distance<Meter> &other) {
    Distance<T1> dist = *this;
    dist.meters += other.meters;
    return dist;
  };

  friend std::ostream &operator<<(std::ostream &os, const Distance<T1> &dist) {
    return os << dist.meters << "m";
  };
};

void t4() {
  Distance<Meter> meters(2);
  meters += 3;

  Distance<Kilometer> kilometers(2);
  kilometers += 3;

  std::cout << "5 meters: " << meters << std::endl;
  std::cout << "5 kilometers: " << kilometers << std::endl;
  std::cout << "5 kilometers + 5 meters: " << kilometers + meters << std::endl;
};

/*
void t5(){
  std::vector<int> vec = {1, 2, 3};

  std::cout << *(vec | Find([](int value) { return value > 1; })) << std::endl;
  std::cout << (vec | Find([](int value) { return value == 5; })) << std::endl;

  std::cout << (vec | Reduce([](int previous_value, int current_value) {
      return previous_value + current_value;
    }, 0)) << std::endl;

  std::cout << (vec | Reduce([](int previous_value, int current_value) {
      return previous_value + 2 * current_value;
    }, 5)) << std::endl;
};
*/
