#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
  std::string name;
  std::string barcode;
  double price;

public:
  Product(const std::string &name, const std::string &barcode, double price);

  std::string getName() const;
  std::string getBarcode() const;
  double getPrice() const;
};

#endif // PRODUCT_H