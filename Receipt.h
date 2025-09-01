#ifndef RECEIPT_H
#define RECEIPT_H

#include "Product.h"
#include <string>
#include <utility>
#include <vector>

class Receipt {
private:
  std::vector<std::pair<Product, int>> items;
  std::string paymentMethod;
  double total = 0.0;
  double paymentAmount = 0.0;
  double change = 0.0;

public:
  void addProduct(const Product &product, int quantity);
  double closeReceipt(const std::string &method, double payment);
  void printReceipt() const;

  double getTotal() const;
  double getChange() const;
  std::string getPaymentMethod() const;
  bool isEmpty() const;
};

#endif // RECEIPT_H