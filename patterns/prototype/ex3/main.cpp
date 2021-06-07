#include <cstdlib>
#include <vector>
#include <iostream>



class Stooge {
public:
    virtual Stooge *clone() = 0;
    virtual void slap_stick() = 0;
};

class Factory {
public:
    static Stooge *make_stooge(int choice);
private:
    static Stooge *s_prototypes[4];

};

// class test {
// public:
//     test() {
//         std::cout << "test class created" << std::endl;
//     }
//     static test *info(){
//         std::cout << "info" << std::endl;
//     }
//     static test info2(){
//         std::cout <<"info2" << std::endl;
//     }
// };

int main() {
    std::vector<Stooge*> roles;
    int32_t choice;

    while (true) {
        std::cout << "L(1) M(2) C(3) G(4): ";
        std::cin >> choice;
        if (choice == 0)
            break;
        roles.push_back(Factory::make_stooge(choice));
    }

    for (int i = 0; i < roles.size(); i++) {
        roles[i]->slap_stick();
    }

    for (int i = 0; i < roles.size(); i++) {
        delete  roles[i];
    }


    return EXIT_SUCCESS;
}

class Larry : public Stooge {
public:
    Stooge *clone() {return new Larry; };
    void slap_stick() {
        std::cout << "Larry: slap head\n";
    }
};

Stooge *Factory::s_prototypes[] = {
    0, new Larry, new Larry, new Larry
};

Stooge *Factory::make_stooge(int choice) {
    return s_prototypes[choice]->clone();
};