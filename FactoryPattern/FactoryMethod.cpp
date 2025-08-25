#include <iostream>
#include <memory>
#include "FactoryMethod.h"

void ConcreteProductMine::print() {
  std::cout << "this=" << this << " print MINE\n";
}

void ConcreteProductYours::print() {
  std::cout << "this=" << this << " print YOURS\n";
}

std::unique_ptr<Product> Creator::create(ProductId id) {
  if (ProductId::MINE == id) {
      return std::make_unique<ConcreteProductMine>();
  }

  else if (ProductId::YOURS == id) {
      return std::make_unique<ConcreteProductYours>();
  }

  return nullptr;
}


