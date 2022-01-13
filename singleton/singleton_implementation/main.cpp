#define _USE_MATH_DEFINES
#define _HAS_AUTO_PTR_ETC 1
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>

#include <boost/lexical_cast.hpp>

// we wanna read the txt file to database
// for us, it only make sense to have one instance of such database
// because you dont want to replicate the information again and again
// So, we're going to make a singleton database effectively
class SingletonDatabase {
    SingletonDatabase() {
        std::cout << "Initializing database\n";
        std::ifstream ifs ("capitals.txt");

        std::string s, s2;

        while (getline(ifs, s)) {
            getline(ifs, s2);
            int population = boost::lexical_cast<int>(s2);
            capitals[s] = population;
        }
    }
    std::map<std::string, int> capitals;
public:
    // those delete ensures that nobody can actually replicate this database in anyway
    // thereby wasting database resources
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator= (SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name) {
        return capitals[name];
    }
};

int main (void)
{
    std::string city = "Tokyo";
    std::cout << city << " has population " <<
        SingletonDatabase::get().get_population(city) << std::endl;
    
    // // Not allowed, because the copy constructor is deleted
    // auto db = SingletonDatabase::get();

    return 0;
}