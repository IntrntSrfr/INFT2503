#include <string>

const double sales_tax = 1.25; // 25%

class Commodity
{
public:
  Commodity(int id_, const std::string &name_, double price_);
  int get_id() const;
  const std::string &get_name() const;
  double get_price() const;
  double get_price(double amt) const;
  double get_price_with_sales_tax(double amt) const;
  void set_price(double price_);

private:
  int id;
  std::string name;
  double price;
};

Commodity::Commodity(int id_, const std::string &name_, double price_) {
  id = id_;
  name = name_;
  price = price_;
}

int Commodity::get_id() const { return id; };
const std::string &Commodity::get_name() const { return name; }
double Commodity::get_price(double amt) const { return amt * price; }
double Commodity::get_price() const { return price; }
void Commodity::set_price(double price_) { price = price_; }
double Commodity::get_price_with_sales_tax(double amt) const { return amt * price * sales_tax; }
