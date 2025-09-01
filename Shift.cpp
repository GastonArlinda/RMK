#include "Shift.h"

#include <iomanip>
#include <iostream>

void Shift::open(const std::string &name, double startingCash) {
  cashierName = name;
  cashInDrawer = startingCash;
  isOpen = true;
  std::cout << "\nСмена открыта:\n"
            << "Кассир: " << cashierName << "\n"
            << "Наличные в кассе: " << std::fixed << std::setprecision(2)
            << cashInDrawer << " руб.\n";
}

void Shift::registerSale(double amount, const std::string paymentMethod) {
  if (paymentMethod == "cash") {
    totalCashSales += amount;
    cashInDrawer += amount;
  } else if (paymentMethod == "card") {
    totalCardSales += amount;
  }
}

void Shift::updateCashDrawer(double delta) { cashInDrawer += delta; }

void Shift::close() {
  if (!isOpen) {
    std::cerr << "Ошибка! Смена не открыта.\n";
    return;
  }
  std::cout << "\n--- Закрытие смены ---\n";
  std::cout << "Кассир: " << cashierName << "\n";
  std::cout << "Продажи наличными: " << std::fixed << std::setprecision(2)
            << totalCashSales << " руб.\n";
  std::cout << "Продажи по карте: " << totalCardSales << " руб.\n";
  std::cout << "Остаток наличности в кассе: " << cashInDrawer << " руб.\n";
  isOpen = false;
}

bool Shift::isShiftOpen() { return isOpen; }

double Shift::getCashInDrawer() const { return cashInDrawer; }