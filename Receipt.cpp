#include <iomanip>
#include <iostream>

#include "Receipt.h"

void Receipt::addProduct(const Product &product, int quantity) {
  items.push_back(std::make_pair(product, quantity));
  total += product.getPrice() * quantity;
}

double Receipt::closeReceipt(const std::string &method, double payment) {
  paymentMethod = method;
  paymentAmount = payment;
  change = 0.0;

  if (method == "cash") {
    if (payment < total) {
      std::cerr << "Ошибка, недостаточно наличных средств для оплаты.\n";
      exit(1);
    }
    change = payment - total;
  }

  return change;
}

void Receipt::printReceipt() const {
  std::cout << "\n========== ЧЕК ==========\n";
  for (const auto &item : items) {
    const Product &product = item.first;
    int quantity = item.second;
    double price = product.getPrice();
    std::cout << product.getName() << " x" << quantity << " = " << std::fixed
              << std::setprecision(2) << price * quantity << " руб.\n";
  }

  std::cout << "--------------------------\n";
  std::cout << "Итого: " << std::fixed << std::setprecision(2) << total
            << " руб.\n";
  std::cout << "Оплата: " << (paymentMethod == "cash" ? "Наличные" : "Карта")
            << "\n";
  std::cout << "Внесено: " << paymentAmount << " руб.\n";
  std::cout << "Сдача: " << change << " руб.\n";
  std::cout << "--------------------------\n";
}

double Receipt::getTotal() const { return total; }

double Receipt::getChange() const { return change; }

std::string Receipt::getPaymentMethod() const { return paymentMethod; }

bool Receipt::isEmpty() const { return items.empty(); }