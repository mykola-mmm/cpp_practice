//Move constructor

#include <iostream>
#include <cstdlib>
#include <vector>

class MemoryBlock {
    private:
    size_t _length;
    int* _data;

    public:
    explicit MemoryBlock(size_t length) : _length(length), _data(new int[length]) {
        std::cout << "In MemBlock(size_t).length = " << _length << "." << std::endl;
    }

    ~MemoryBlock() {
        std::cout << "In ~MemBlock(size_t).length = " << _length << "." << std::endl;
        if (_data != nullptr) {
            std::cout << "Deleting _data" << std::endl;
            delete[] _data;
        }
    }

    //Copy constructor
    MemoryBlock(const MemoryBlock& other) : _length(other._length), _data(new int[other._length]) {
        std::cout << "In MemoryBlock(const MemoryBlock&). length = "
            << other._length << ". Copying resource." << std::endl;
        
        std::copy(other._data, other._data + _length, _data);
    }

    //Copy assignment opeartor
    MemoryBlock& operator=(const MemoryBlock& other) {
        std::cout << "In operator=(const MemoryBlock&). length = "
            << other._length << ". Copying resource." << std::endl;

        if (this != &other) {
            delete[] _data;
            _length = other._length;
            _data = new int[_length];
            std::copy(other._data, other._data + _length, _data);
        }
        return *this;
    }

    size_t Length() const {
        return _length;
    }
};


int main() {

    //vector<MemoryBlock> v;
    MemoryBlock* ex = new MemoryBlock(10);
    auto ex2 = ex;
    delete ex;
    return EXIT_SUCCESS;
}