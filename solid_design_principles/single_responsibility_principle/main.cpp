#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

// Single responsibility principle
// A class should have a single main responsibility 
// and it should not be overtaken by other jobs

struct Journal {
    std::string title;
    std::vector<std::string> entries;

    Journal(const std::string& title) : title{title} {}

    void add_entry (const std::string& entry){
        static int count = 1;
        entries.push_back(boost::lexical_cast<std::string>(count++) + "; " + entry);
    }

    // // This is a NOT good implementation
    // // Because what if you wanna do save to others
    // // or do change,
    // // then you have to change every single one of them
    // void save(const std::string& filename) {
    //     std::ofstream ofs (filename);
    //     for (auto& e : entries) {
    //         ofs << e << std::endl;
    //     }
    // }
};

// Seperation of concern
// As Persistence Manager grow
// You have all that utility codes in a single place
struct PersistenceManager {
    static void save(const Journal& journal, const std::string& filename) {
        std::ofstream ofs (filename);
        for (auto& e : journal.entries) {
            ofs << e << std::endl;
        }
    }
};

// This is a gist of single responsibility principle
// The journal is responsible for its own title and entries 
// and the way you work with them,
// But when it comes to persistence, 
// it makes more sense to seperate out this concern

int main (void) 
{
    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I laughed today");

    // Journal.save("diary.txt")

    PersistenceManager pm;
    pm.save(journal, "diary.txt");

    return 0;
}