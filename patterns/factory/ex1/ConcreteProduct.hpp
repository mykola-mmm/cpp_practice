#ifndef CONCRETEPRODUCT_HPP
#define CONCRETEPRODUCT_HPP

#include "Product.hpp"

class ConcreteProduct1 : public Product {
    std::string Operation() const override {
        return "{Result of ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product {
    std::string Operation() const override {
        return "{Result od ConcreteProduct2}";
    }
};

#endif