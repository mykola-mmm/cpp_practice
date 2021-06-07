#include <iostream>
#include <cstdlib>

void Print(int *i) {
    std::cout << i << std::endl;
    std::cout << &i << std::endl;
};

void Print2(int i) {
    std::cout << i << std::endl;
    std::cout << &i << std::endl;
}


int main(void) {
    int i = 100000;
    Print(i);   // prints 0x186a0 and 0x7ffe20d62c58
    Print2(i);  // prints 100000 and 0x7fff7b38cc8c



    return EXIT_SUCCESS;
}