#ifndef CONCRETEPRODUCT_HPP
#define CONCRETEPRODUCT_HPP

#include "Product.hpp"

class ConcreteProduct : public Product {
    std::string Operation() const override {
        return "CONCRETE PRODUCT\n";
    }
};


#endif