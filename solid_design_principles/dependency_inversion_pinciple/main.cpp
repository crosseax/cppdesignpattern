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
    // below is the worst thing to do
    // because it violates point A above
    Research(Relationships& relationships) {
        // and it's accessing the low-level module's data
        auto& relations = relationships.relations;
        for (auto&& [first, rel, second] : relations) { // for C++17
            if (first.name == "John" && rel == Relationship::parent) {
                std::cout << "John has a child called " << second.name << std::endl;
            }
        }
    }
    // if the low-level decides to change storage
    // like hiding the relations by making it private
    // then this high level module would be completely broken
};


int main (void)
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);

    return 0;
}