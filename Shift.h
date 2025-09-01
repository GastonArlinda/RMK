#ifndef SHIFT_H
#define SHIFT_H

#include <string>

class Shift {
private:
  std::string cashierName;
  double cashInDrawer = 0.0;
  double totalCashSales = 0.0;
  double totalCardSales = 0.0;
  bool isOpen = false;

public:
  void open(const std::string &name, double startingCash);
  void registerSale(double amount, const std::string paymentMethod);
  void updateCashDrawer(double delta);
  void close();
  bool isShiftOpen();
  double getCashInDrawer() const;
};

#endif // SHIFT_H