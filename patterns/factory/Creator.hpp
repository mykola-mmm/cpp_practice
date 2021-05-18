#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "ConcreteProduct.hpp"
#include "Product.hpp"

class Creator {
    private:

    public:

    virtual Creator::~Creator();
    virtual Product* FactoryMethod() const = 0;
    std::string SomeOperation() const;
};
#endif