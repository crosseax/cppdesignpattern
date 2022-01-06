#include <string>
#include <iostream>
#include "gtest/gtest.h"


struct Person {
    int id;
    std::string name;
};

class PersonFactory {
    int id{0};
public:
    Person create_person(const std::string& name) {
        return {id++, name}
    }
};