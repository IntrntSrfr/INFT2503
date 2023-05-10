#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <thread>

void t1();
void t2();
void t3();
void t4();
void t5();

int main() {
  t1();
  t2();
  t3();
  t4();
  t5();
  return 0;
}

int getAnswer() { return 42; }

void getAnswer(int &num) { num = 42; }

void getAnswer(int *&num) { num = new int(42); }

void getAnswer(const std::function<void(int)> &lambda) { lambda(42); }

void t1() {
  std::cout << getAnswer() << std::endl;

  int answer1;
  getAnswer(answer1);
  std::cout << answer1 << std::endl;

  int *answer2;
  getAnswer(answer2);
  std::cout << *answer2 << std::endl;
  delete answer2;

  getAnswer([](int answer) { std::cout << answer << std::endl; });
}

class Button {
  public:
    Button(std::string label_, std::function<void()> on_click_) 
      : label(label_), on_click(on_click_) {};
    virtual ~Button(){};
    
    std::string label;
    std::function<void()> on_click;

    virtual void activate() {
      if(on_click)
        on_click();
    };
    
    friend std::ostream &operator<<(std::ostream &os, const Button &button) {
      return os << button.string();
    };

    virtual std::string string() const = 0;    
};

class ToggleButton : public Button {
  public:
  ToggleButton(std::string label_, bool state_, std::function<const void()> on_click_) 
    : Button(label_, on_click_), state(state_) {};

  bool state;

  void activate() override{
    state = !state;
    Button::activate();
  }
  std::string string() const override{
    return "ToggleButton, label: " + label + ", value: " + (state ? "toggled" : "not toggled");
  }
};

class LinkButton : public Button {
  public:
  LinkButton(std::string label_, std::string link_, std::function<const void()> on_click_)
    : Button(label_, on_click_), link(link_) {};

  std::string link;

  void activate() override{
    Button::activate();
  }
  std::string string() const override {
    return "LinkButton, label: " + label + ", link: " + link;
  }
};

void t2() {
  std::vector<std::unique_ptr<Button>> buttons;

  buttons.emplace_back(std::make_unique<ToggleButton>("Toggle something", true, [] {
    std::cout << "Toggled something" << std::endl;
  }));

  buttons.emplace_back(std::make_unique<LinkButton>("Link to somewhere", "https://ntnu.no", [] {
    std::cout << "Opened link" << std::endl;
  }));

  for (auto &button : buttons) {
    std::cout << *button << std::endl;
    button->activate();
    std::cout << *button << std::endl;
  }
};

template <typename T1>
class Angle {
  public:
  Angle(int value_) : value(value_ % 360) {};
  Angle(double value_) : value(fmod(value_, 3.14159265359)) {};

  T1 value;

  friend std::ostream &operator<<(std::ostream &os, Angle &angle) {
    return os << angle.value;
  };
};

void t3() {
  Angle<int> angle1(30);
  std::cout << angle1 << std::endl;

  Angle<int> angle2(390);
  std::cout << angle2 << std::endl;

  Angle<double> angle3(3.14159265359 / 2);
  std::cout << angle3 << std::endl;

  Angle<double> angle4(3.14159265359 * 1.5);
  std::cout << angle4 << std::endl;
};

void parallell_transform(std::vector<int> &vec, int num_threads, const std::function<int(int)> &lambda) {
  std::vector<std::thread> threads;



};

void t4() {
  std::vector<int> vec = {1, 2, 3, 4, 5, 6};

  parallell_transform(vec, 4, [](int e) {
    return e * 2;
  });

  for (auto &e : vec)
    std::cout << e << '\n';
};

template <typename T1>
std::ostream &operator<<(std::ostream &os, const std::vector<T1> &vec){
  int size = vec.size();
  os << '{';
  for(int i = 0; i < size-1; i++)
    os << vec[i] << ", ";
  if(size > 0)
    os << vec[size-1];
  os << '}';
  return os;
};

std::vector<int> operator*(const std::vector<int> &self, const int &num){
  std::vector<int> res;
  for(int i = 0; i < self.size(); i++)
    res.push_back(self[i]*num);
  return res;
};

std::vector<int> operator*(const std::vector<int> &self, const std::vector<int> &other){
  std::vector<int> res;
  for(int i = 0; i < self.size() && i < other.size(); i++)
    res.push_back(self[i]*other[i]);
  return res;
};

void t5(){
  std::cout << std::vector<int>() << std::endl;
  std::cout << std::vector<float>({1.5, 2.5}) << std::endl;

  std::vector<int> vec = {1, 2, 3};
  std::cout << vec << std::endl;
  std::cout << vec * 3 << std::endl;
  std::cout << vec * vec << std::endl;
}