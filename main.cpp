#include "Product.h"
#include "ProductDatabase.h"
#include "Receipt.h"
#include "Shift.h"

#include <iostream>
#include <locale>

void showCommands() {
  std::cout << "\nКоманды:\n"
            << " - search    : Начать новый чек (режим поиска)\n"
            << " - db        : Показать все товары\n"
            << " - close     : Закрыть текущий чек и завершить смену\n";
}

void processPayment(Receipt &receipt, Shift &shift) {
  std::string paymentMethod;
  std::cout << "Итог =" << receipt.getTotal() << "\nОплата (cash/card): ";
  std::cin >> paymentMethod;

  double payment = 0.0;

  if (paymentMethod == "cash") {
    std::cout << "Введите сумму, внесенную покупателем: ";
    std::cin >> payment;
    if (std::cin.fail() || payment < 0) {
        std::cerr << "Ошибка: введено некорректное число.\n";
        exit(1);
    }
  } else if (paymentMethod == "card") {
    payment = receipt.getTotal();
  } else {
    std::cout << "Неизвестный способ оплаты.\n";
    return;
  }

  double change = receipt.closeReceipt(paymentMethod, payment);

  shift.registerSale(payment, paymentMethod);

  if (paymentMethod == "cash") {
    shift.updateCashDrawer(-change);
  }
  receipt.printReceipt();
}

void processReceiptSession(ProductDatabase &db, Shift &shift) {
  Receipt receipt;

  std::cout << "\nВход в режим чека.\nВведите штрих-код/название товара или "
               "'end' для завершения:\n";
  db.getAll();
  while (true) {
    std::string input;
    std::cout << ">> ";
    std::cin >> input;

    if (input == "end" || input == "close") {
      if (!receipt.isEmpty()) {
        processPayment(receipt, shift);
      } else {
        std::cout << "Чек пуст, нечего печатать.\n";
      }

      if (input == "close") {
        shift.close();
        exit(0);
      }

      break;
    }

    const Product *product = db.findByBarcode(input);
    if (!product) {
      product = db.findByName(input);
    }

    if (!product) {
      std::cout << "Товар не найден.\n";
      continue;
    }

    int quantity;
    std::cout << "Введите количество товара \"" << product->getName() << "\": ";
    std::cin >> quantity;

    if (quantity <= 0 || std::cin.fail()) {
      std::cin.clear();
      std::cout << "Некорректное количество.\n";
      continue;
    }

    receipt.addProduct(*product, quantity);
  }
}

int main() {
  ProductDatabase db;
  db.loadFromCSV("products.csv");

  Shift shift;
  std::string cashierName;
  double startingCash;

  std::cout << "Введите имя кассира: ";
  std::getline(std::cin, cashierName);

  std::cout << "Введите сумму наличностей в кассе: ";
  std::cin >> startingCash;

  if (std::cin.fail() || startingCash < 0) {
    std::cerr << "Ошибка: введено некорректное число.\n";
    return 1;
  }

  shift.open(cashierName, startingCash);
  showCommands();

  while (true) {
    std::string command;
    std::cout << "\nКоманда (search/db/close): ";
    std::cin >> command;

    if (command == "search") {
      processReceiptSession(db, shift);
    } else if (command == "db") {
      db.getAll();
    } else if (command == "close") {
      shift.close();
      break;
    } else {
      std::cout << "Неизвестная команда.\n";
      showCommands();
    }
  }

  return 0;
}