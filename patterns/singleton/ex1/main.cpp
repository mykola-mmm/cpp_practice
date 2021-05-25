
#include <iostream>
#include <math.h>
#include <map>
#include <string>
#include <fstream>


using namespace std;

class SingletonDatabase {
    std::map<std::string, int32_t> m_country;

    SingletonDatabase() {
        std::ifstream ifs("country.txt");
        std::string city, population;

        while(getline(ifs,city)) {
            getline(ifs, population);
            m_country[city] = stoi(population);
        }
    }

    public:
    // COPY CONSTRUCTOR
    SingletonDatabase(SingletonDatabase const &) = delete;
    //ASSIGNMENT OPERATOR
    SingletonDatabase &operator=(SingletonDatabase const &) = delete;

    static SingletonDatabase &get() {
        static SingletonDatabase db;
        return db;
    }

    int32_t get_population(const std::string &name) {return m_country[name]; }
};

int main() {
    //SingletonDatabase df;
    //std::cout << (SingletonDatabase::get().get_population("USA")) << std::endl;
    return EXIT_SUCCESS;
}