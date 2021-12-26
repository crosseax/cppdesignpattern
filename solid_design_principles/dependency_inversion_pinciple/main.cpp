#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

// #include <boost/lexical_cast.hpp>

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstraction
// B. Abstractions should not depend on details.
//    Details should depend on abstractions

// When talking about abstractions, generally 
// we're talking about interfaces or base classes

enum class Relationship {
    parent,
    child, 
    sibling
};

struct Person {
    std::string name;
};

// The struct below, Relationships
// is typically called:
// Low-level module/construct 
// because what it does essentially is 
// to provide functionality for data storage
// and a couple of utility functions to populate that storage
struct Relationships { 
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }
};

// if you want to perform a research on a data,
// this will be called a High-level module
struct Research {
    
};

int main (void)
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);



    return 0;
}