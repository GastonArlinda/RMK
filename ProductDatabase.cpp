#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

#include "ProductDatabase.h"

bool ProductDatabase::loadFromCSV(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть фйал " << filename << std::endl;
    return false;
  }

  std::string line;

  // Пропускаем первую строку "Наименование,Штрих-Код,Цена"
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string name, barcode, priceStr;

    std::getline(ss, name, ',');
    std::getline(ss, barcode, ',');
    std::getline(ss, priceStr, ',');

    if (name.empty() || barcode.empty() || priceStr.empty()) {
      std::cerr << "Некорректная строка: " << line << std::endl;
      continue;
    }

    double price = std::stod(priceStr);
    products.emplace_back(name, barcode, price);
  }

  file.close();
  return true;
}

const Product *ProductDatabase::findByBarcode(const std::string &barcode) {
  for (const auto &product : products) {
    if (product.getBarcode() == barcode) {
      return &product;
    }
  }
  return nullptr;
}

std::string toUpper(const std::string &input) {
  std::string result;
  for (char c : input) {
    result += std::toupper(c);
  }
  return result;
}

const Product *ProductDatabase::findByName(const std::string &namePart) {
  // Работает только с латинскими символами
  // Символы кириллицы многобайтные, toupper такие не поддерживает
  std::string upperPart = toUpper(namePart);
  for (const auto &product : products) {
    if (product.getName().find(upperPart) != std::string::npos) {
      return &product;
    }
  }
  return nullptr;
}

void ProductDatabase::getAll() {
  for (const auto &product : products) {
    std::cout << product.getName() << " - " << product.getPrice() << " руб. - "
              << product.getBarcode() << std::endl;
  }
}
