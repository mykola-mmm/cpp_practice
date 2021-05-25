#include <iostream>


class AbstractProduct {
    public:
    virtual ~AbstractProduct(){};
    virtual std::string SomeFunction() const = 0;
};

class ConcreteProduct : public AbstractProduct {
    public:
    std::string SomeFunction() const override {
        return "Result of the ConcreteProduct func";
    }
};

class AbstractProduct2 {
    public:
    virtual ~AbstractProduct2(){};
    virtual std::string SomeFunction() const = 0;
};

class ConcreteProduct2 : public AbstractProduct2 {
    public:
    std::string SomeFunction() const override {
        return "Result of the ConcreteProduct2 func";
    }
};

class AbstractFactory {
    public:
    virtual AbstractProduct* CreateProductA() const = 0;
    virtual AbstractProduct2* CreateProductA2() const = 0;
};

class ConcreteFactory : public AbstractFactory{
    public:
    AbstractProduct* CreateProductA() const override {
        return new ConcreteProduct();
    }
    AbstractProduct2* CreateProductA2() const override {
        return new ConcreteProduct2();
    }
};

void Client(const AbstractFactory &af) {
    const AbstractProduct* a = af.CreateProductA();
    std::cout << a->SomeFunction() << std::endl;
    const AbstractProduct2* b = af.CreateProductA2();
    std::cout << b->SomeFunction() << std::endl;
    delete a;
    delete b;
};

int main() {
    ConcreteFactory* cf = new ConcreteFactory();
    Client(*cf);
    //auto p = cf->CreateProductA();
    return EXIT_SUCCESS;
}