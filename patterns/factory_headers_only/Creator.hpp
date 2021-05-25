#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "ConcreteProduct.hpp"
#include "Product.hpp"
#include <iostream>

class Creator {
    private:
    public:

    virtual ~Creator(){};
    virtual Product* FactoryMethod() const = 0;
    std::string SomeOperation() const {
        Product* product = this->FactoryMethod();
        std::string result = "Creator of " + product->Operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 : public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

void ClientCode(const Creator& creator) {
    std::cout << "Client not aware of creator" << creator.SomeOperation() << std::endl;
}

#endif