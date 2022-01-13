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


// when you want to test this, all problems show up
struct SingletonRecordFinder {
    int total_population(std::vector<std::string> names) {
        int result{0};
        for (auto& name : names) {
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};
// because there is no way to substitute this strongly-tied database
// the test have to use the values taken from the actual file
// watch https://www.udemy.com/course/patterns-cplusplus/learn/lecture/7736768#content

// basically, in order to run the test, due to the accessibility of the singleton database
// the test is going to go through many abundant stages of retrieving the data by yourself(tester per se)
// including configurations and many other settings
// this is extremely inconvinient 

// hence such test is not a unit test, but a integration test
// as a result, there will not be a proper unit test
// if the data changes, the test is also going to face potential danger

int main (void)
{
    std::string city = "Tokyo";
    std::cout << city << " has population " <<
        SingletonDatabase::get().get_population(city) << std::endl;
    
    // // Not allowed, because the copy constructor is deleted
    // auto db = SingletonDatabase::get();

    return 0;
}