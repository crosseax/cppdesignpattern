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

    void save(const std::string& filename) {
        std::ofstream ofs (filename);
        for (auto& e : entries) {
            ofs << e << std::endl;
        }
    }

};


int main (void) 
{
    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I laughed today");

    return 0;
}