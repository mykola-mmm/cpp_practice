#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <exception>

class Item {
    public:
    Item() { std::cout << "ITEM AQUIRES" << std::endl; }
    ~Item() { std::cout << "ITEM DESTROYED" << std::endl; }
};

void ex1(void) {
    std::shared_ptr<__int32_t> sh_ptr = std::make_shared<__int32_t>(2);
    std::cout << "std::shared_ptr<__int32_t> sh_ptr = std::make_shared<__int32_t>(2);\t" << sh_ptr.use_count() << std::endl;
    //1

    auto a = sh_ptr;
    std::cout << "auto a = sh_ptr;\t" << sh_ptr.use_count() << std::endl;
    //2

    auto b = a;
    std::cout << "auto b = a;\t" << sh_ptr.use_count() << std::endl;
    //3

    //auto i = b.release();
    //std::cout << "b.release();\t" << sh_ptr.use_count() << std::endl;

    a.reset();
    std::cout << "a.reset();\t" << sh_ptr.use_count() << std::endl;
    //2
    {
        auto e = b;
        std::cout << "auto e = b;\t" << sh_ptr.use_count() << std::endl;
        //3
        //Because {} - new scope
    }

    std::cout << "auto c = b.get();\t" << sh_ptr.use_count() << std::endl;
    //2
    //Because previous {} has finished

    auto c = b.get();
    auto d = c;
    auto e = c;
    std::cout << "auto c = b.get();\t" << sh_ptr.use_count() << std::endl;
    //2
    //Because std::sh_ptr.get() - 
    
}

void ex2(void) {
    Item *item1 = new Item;
    std::shared_ptr<Item> ptr1(item1);

    Item *item4 = new Item;

    {
        std::cout << "\tnew scope start\n";
        auto *item2 = new Item;
        delete item2;
        std::cout << "\n";
        auto *item3 = new Item;
        std::shared_ptr<Item> ptr3(item3);
        std::shared_ptr<Item> ptr4(item4);

        std::cout << "\tnew scope end\n";
    }
    //item1, item3, item4 is gonna be destroyed after scope returns to main
}

void shared_ptr_exception(void) {
    try{
            {
                Item *item1 = new Item;
                std::shared_ptr<Item> ptr1(item1);
                std::shared_ptr<Item> ptr2(item1);
            }
    } catch (std::exception &e) {
        //std::cout << e.what() << std::endl;
    }
    // result:
    // ITEM AQUIRES
    // ITEM DESTROYED
    // ITEM DESTROYED
    // free(): double free detected in tcache 2
    // Aborted (core dumped)
    //
    //Because ptr1 destroys item1 first and then ptr2 try to destroy it again

}

void shared_ptr_exception_solution(void) {
    Item *item1 = new Item;
    auto ptr1 = std::make_shared<Item> (*item1);
    auto ptr2 = std::make_shared<Item> (*item1);
    auto ptr3 = std::make_shared<Item> (*item1);
    auto ptr4 = ptr1;
    //or


}


int main(void) {
    ex1();
    std::cout << "\n\n\n" << std::endl;
    ex2();
    std::cout << "\n\n\n" << std::endl;
    // try not working
    try {
        //shared_ptr_exception();
    } catch (std::exception &e) {
        std::cout << "\t" << e.what() << std::endl;
    }
    std::cout << "\n\n\n" << std::endl;
    shared_ptr_exception_solution();

    return EXIT_SUCCESS;    //<cstdlib>
}


