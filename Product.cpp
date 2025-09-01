#include "Product.h"

Product::Product(const std::string &name, const std::string &barcode,
                 double price)
    : name(name), barcode(barcode), price(price) {}

std::string Product::getName() const { return name; }

std::string Product::getBarcode() const { return barcode; }

double Product::getPrice() const { return price; }