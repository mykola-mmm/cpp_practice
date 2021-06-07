#include <cstdlib>
#include <iostream>
#include <string>

template<typename T>
void f(const T &param) {
    std::cout << std::to_string(param) << " of type " << typeid(param).name() << std::endl;
}

template<typename T>
void f2(T *param) {
    std::cout << std::to_string(*param) << " of type " << typeid(*param).name() << std::endl;
}

template<typename T>
void f3(T &&param) {
    std::cout << std::to_string(param) << " of type " << typeid(param).name() << std::endl;
}


int main() {

    int x = 27;
    const int cx = x;
    const int &rx = x;

    f3(x);
    f3(cx);
    f3(rx);

    return EXIT_SUCCESS;
}