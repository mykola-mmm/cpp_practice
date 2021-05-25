#include "Product.hpp"
#include "ConcreteProduct.hpp"
#include "Creator.hpp"

#include <iostream>

int main(void) {
    std::cout << "main" << std::endl;
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    //Product test;
    
}