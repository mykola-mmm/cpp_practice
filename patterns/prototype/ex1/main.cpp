#include <cstdlib>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <functional>

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype {
protected:
    std::string _prototype_name;
    float _prototype_field;

public:
    Prototype() {};
    Prototype(std::string prototype_name): _prototype_name(prototype_name) {};
    virtual ~Prototype() {};
    virtual Prototype *Clone() const = 0;
    virtual void Method(float prototype_field) {
        this->_prototype_field = prototype_field;
        std::cout << "Call Method from " << _prototype_name << " with filed: " << prototype_field << std::endl;
    }
};

class ConcretePrototype1 : public Prototype {
private:
    float _concrete_prototype_field1;

public:
    ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
    : Prototype(prototype_name), _concrete_prototype_field1(concrete_prototype_field) {};

    Prototype *Clone() const override {
        return new ConcretePrototype1(*this);
    }

};

class ConcretePrototype2 : public Prototype {
private:
    float _concrete_prototype_field2;

public:
    ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
    : Prototype(prototype_name), _concrete_prototype_field2(concrete_prototype_field) {}

    Prototype *Clone() const override {
        return new ConcretePrototype2(*this);
    }
};



class PrototypeFactory {
private:
    std::unordered_map<Type, Prototype*, std::hash<int>> m_prototypes;

public:
    PrototypeFactory() {
        m_prototypes[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        m_prototypes[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    ~PrototypeFactory() {
        delete m_prototypes[Type::PROTOTYPE_1];
        delete m_prototypes[Type::PROTOTYPE_2];
    }

    Prototype *CreatePrototype(Type type) {
        return m_prototypes[type]->Clone();
    }
};

void Client(PrototypeFactory &prototype_factory) {
    std::cout << "Lets create a Prototype" << std::endl;

    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    std::cout << "\n";

    std::cout << "Lets create a Prototype 2" << std::endl;
    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(1000);
    delete prototype;
}

int main() {
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return EXIT_SUCCESS;
}