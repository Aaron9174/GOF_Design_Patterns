#include <iostream>
#include <memory>

enum ProductId {MINE, YOURS};

class Product {
public:
    virtual void print() = 0;
    virtual ~Product() = default;
};

class ConcreteProductMine: public Product {
public:
    void print() {
        std::cout << "this=" << this << " print MINE\n";
    }
};

class ConcreteProductYours: public Product {
public:
    void print() {
        std::cout << "this=" << this << " print YOURS\n";
    }
};

class Creator {
public:
    virtual std::unique_ptr<Product> create(ProductId id) {
        if (ProductId::MINE == id) {
            return std::make_unique<ConcreteProductMine>();
        }

        if (ProductId::YOURS == id) {
            return std::make_unique<ConcreteProductYours>();
        }

        return nullptr;
    }

    virtual ~Creator() = default;
};

int main() {
    // The unique_ptr prevents memory leaks
    std::unique_ptr<Creator> creator = std::make_unique<Creator>();
    std::unique_ptr<Product> product = creator->create(ProductId::MINE);
    product->print();

    product = creator->create(ProductId::YOURS);
    product->print();
}