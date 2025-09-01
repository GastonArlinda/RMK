#ifndef PRODUCT_DATABASE_H
#define PRODUCT_DATABASE_H

#include "Product.h"
#include <string>
#include <vector>

class ProductDatabase {
private:
  std::vector<Product> products;

public:
  bool loadFromCSV(const std::string &filename);
  const Product *findByBarcode(const std::string &barcode);
  const Product *findByName(const std::string &name);
  void getAll();
};

#endif // PRODUCT_DATABASE_H