//https://www.youtube.com/watch?v=zuegQmMdy8M
//https://www.youtube.com/watch?v=q_LUYLV3l44
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdio.h>

void ptr_basic(void) {
    int a = 10;
    int* b;
    b = &a;
    std::cout << "a = " << a << std::endl;
    std::cout << "*b = " << *b << std::endl;
    std::cout << "&a = " << &a << std::endl;
    std::cout << "&b = " << &b << std::endl;
}

void ptr_basic2(void) {
    int amtToStore;
    std::cout << "num of numbers to store : ";
    std::cin >> amtToStore;
    int* pNums;
    pNums = (int *) malloc(amtToStore * sizeof(int));
    if(pNums != NULL) {
        int i = 0;
        while(i < amtToStore) {
            std::cout << "ENTER a NUM : ";
            std::cin >> pNums[i];
            ++i;
        }
    }
    std::cout << "You entered : \n";
    for(int i = 0; i < amtToStore; ++i) {
        std::cout << pNums[i] << std::endl;
    }

    //std::cout << "sizeof pNums " << sizeof(pNums) << std::endl;

    delete[] pNums;
}

void unique_basic(void) {
    int amtToStore;
    std::cout << "num of numbers to store : ";
    std::cin >> amtToStore;
    std::unique_ptr<int[]> pNums(new int[amtToStore]);
    //std::unique_ptr<int[]> pNums2 = pNums;    //illegal
    if(pNums != NULL) {
        int i = 0;
        while(i < amtToStore) {
            std::cout << "ENTER a NUM : ";
            std::cin >> pNums[i];
            ++i;
        }
    }
    std::cout << "You entered : \n";
    for(int i = 0; i < amtToStore; ++i) {
        std::cout << pNums[i] << std::endl;
    }

    //std::cout << "sizeof pNums " << sizeof(pNums) << std::endl;

}

class Entity {
private:
    int _a;
public:
    Entity(int a) {
        _a = a;
        std::cout << "Entity created\n";
    }

    ~Entity() {
        std::cout << "Entity destroyed\n";
    }

    void Print() {
        std::cout << "Print func called\n";
    }

    void PrintA() {
        std::cout << "The a value is " << _a << std::endl;
    }
};


int main(void) {
    {
        std::unique_ptr<Entity> entity(new Entity(1));  //usual way
        std::unique_ptr<Entity> entity2 = std::make_unique<Entity>(2);   //preferred way 
                                                                        //because of the exception safety
        
        std::cout << "modifiers test\n";
        entity->PrintA();
        std::cout << entity.get() << std::endl;
        entity.release();   // releases the ownership of the managed object
        std::cout << entity.get() << std::endl; 

        entity = std::make_unique<Entity>(10);
        entity->PrintA();
        entity.reset(new Entity(15));
        entity->PrintA();

        std::cout << "SWAP EXAMPLE\n";
        entity->PrintA();
        entity2->PrintA();

        entity.swap(entity2);

        entity->PrintA();
        entity2->PrintA();

        std::cout << "Observers test\n";
        std::cout << ".get() " << entity.get() << std::endl;
        std::cout << ".get_deleter() \n";
        entity.get_deleter();   // NE PONYAL SHO DELAET
        std::cout << ".get_deleter() \n";
        
        std::cout << ".operator_bool \n";
    }

    {
        std::cout << "\nshared pointer\n" << std::endl;
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(2);

    
        std::cout << ".use_count()\n";
        std::cout << entity.use_count() << std::endl;
        std::shared_ptr<Entity> entity2 = entity;
        std::cout << entity.use_count() << std::endl;
        std::weak_ptr<Entity> entity3 = entity; //does not increase reference count
        std::cout << entity.use_count() << std::endl;

        std::cout << ".unique()\n";
        std::cout << entity.unique() << std::endl;
        entity2.reset();
        std::cout << entity.unique() << std::endl;

        std::cout << ".owner before\n";
        entity2 = entity;
        std::cout << entity.owner_before(entity2) << std::endl;
        std::cout << entity2.owner_before(entity) << std::endl;

    
        //entity = std::make_shared<Entity>(12);
        std::shared_ptr<Entity> entity4 = std::make_shared<Entity>(12);

        std::cout << entity.owner_before(entity4) << std::endl;
        std::cout << entity4.owner_before(entity) << std::endl;
    }
    //ptr_basic();
    //ptr_basic2();
    return EXIT_SUCCESS;
}