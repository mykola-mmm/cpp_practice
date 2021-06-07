#include <cstdlib>
#include <string>
#include <iostream>
#include <memory>

struct Office {
    std::string     m_street;
    std::string     m_city;
    int32_t         m_cubical;
};

class Employee {
    std::string     m_name;
    Office          *m_office;

    Employee(std::string name, Office *office) : m_name(name), m_office(office) {}
    friend class EmployeeFactory;

public:
    Employee(const Employee &rhs) : m_name{rhs.m_name}, m_office{new Office{*rhs.m_office}} {}

    Employee& operator=(const Employee &rhs) {
        if (this == &rhs) return *this;
        m_name = rhs.m_name;
        m_office = new Office{*rhs.m_office};
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Employee &o) {
        return os << o.m_name << " works at " << o.m_office->m_street
        << " " << o.m_office->m_city << " seats @" << o.m_office->m_cubical;
    }
};

class EmployeeFactory {
    static Employee main;
    static Employee aux;
    static std::unique_ptr<Employee> NewEmployee(std::string n, int32_t c, Employee &proto) {
        auto e = std::make_unique<Employee>(proto);
        e->m_name = n;
        e->m_office->m_cubical = c;
        return e;
    }

public:
    static std::unique_ptr<Employee> NewMainOfficeEmployee(std::string name, int32_t cubical) {
        return NewEmployee(name, cubical, main);
    }
    static std::unique_ptr<Employee> NewAuxOfficeEmployee(std::string name, int32_t cubical) {
        return NewEmployee(name, cubical, aux);
    }
};

Employee EmployeeFactory::main{"", new Office{"123 East Dr", "London", 123}};
Employee EmployeeFactory::aux{"", new Office{"RMZ Ecoworld ORR", "London", 123}};

int main() {

    auto jane = EmployeeFactory::NewMainOfficeEmployee("Jane Doe", 125);
    auto jack = EmployeeFactory::NewAuxOfficeEmployee("Jack Doe", 123);

    std::cout << *jane << std::endl << *jack << std::endl;

    return EXIT_SUCCESS;
}