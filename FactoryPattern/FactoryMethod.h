
enum ProductId {MINE, YOURS};

class Product {
public:
    virtual void print() = 0;
    virtual ~Product() = default;
};

class ConcreteProductMine: public Product {
public:
    void print();
};

class ConcreteProductYours: public Product {
public:
    void print();
};

class Creator {
public:
    virtual std::unique_ptr<Product> create(ProductId id);

    virtual ~Creator() = default;
};
