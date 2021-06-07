
#include <iostream>
#include <cstdlib>
#include <exception>

class Base {
    public:
    Base() {}
    ~Base() {
        throw 42;
    }
};

int main() {

try {
    Base a;
    //throw 11;
} catch (int a) {
    std::cout << a;
}

    // return EXIT_SUCCESS;
}