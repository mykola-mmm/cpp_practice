#include <cstdlib>
#include <iostream>

class Base {
    public:
    Base() = default;
    ~Base() = default;
};

class Derived: public Base {
    public:
    explicit Derived() : Base() { std::cout << "DERIVED CONSTRUCTOR\n";};
    ~Derived() {};
};

int main() {
    Base *ex = new Base();
    Derived *ex1;
    ex1 = static_cast<Derived*>(ex);

    Derived *ex2 = new Base();
    return EXIT_SUCCESS;
}