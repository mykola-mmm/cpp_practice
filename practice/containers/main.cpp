#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <exception>

int main(void) {
    std::vector<int32_t> v;

    for(int i = 0; i < 100; ++i) {
        v.push_back(i);
    }

    std::cout << "element access\n";
    std::cout << v.at(0) << std::endl;
    std::cout << v.at(10) << std::endl;
    try {
        std::cout << v.at(1000) << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    //std::cout << v.operator[10] << std::endl;
    return EXIT_SUCCESS;
}