
#include <iostream>
#include <math.h>
#include <map>
#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <thread>


class Singleton {

private:
    static Singleton *m_instance;
    static std::mutex m_mutex;

protected:
    Singleton(const std::string value): m_value(value) {};
    ~Singleton() {};
    std::string m_value;

public:
    Singleton(Singleton &) = delete;
    void operator=(const Singleton &) = delete;
    
    static Singleton *GetInstance(const std::string &value);

    void SomeLogic() {};

    std::string value() const {
        return m_value;
    }
};

Singleton *Singleton::m_instance{nullptr};
std::mutex Singleton::m_mutex;

Singleton *Singleton::GetInstance(const std::string &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_instance == nullptr) {
        m_instance = new Singleton(value);
    }
    return m_instance;
}

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singletone = Singleton::GetInstance("FOO");
    std::cout << singletone->value() << std::endl;
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << std::endl;
}

int main() {
    std::thread t1(ThreadBar);
    std::thread t2(ThreadFoo);

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}   