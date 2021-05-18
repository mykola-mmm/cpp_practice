#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
    private:

    public:
    
    virtual ~Product();
    virtual std::string Operation() const = 0; // const = 0 -> pure virtual method
};

#endif