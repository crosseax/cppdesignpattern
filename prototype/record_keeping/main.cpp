#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

struct Address {
    std::string street, city;
    int suite;

    Address (const std::string& street, const std::string& city, int suite)
        : street {street}, city {city}, suite{suite} {}
};

struct Contact {
    std::string name;
    Address address;

    Contact (const std::string& name, const Address& address) 
        : name {name}, address {address} {}
};


int main (void)
{
    Contact john {"John Doe", Address{"123 East Dr", "London", 123}};
    Contact jane {"Jane Smith", Address{"123 East Dr", "London", 103}};
    // is it really worth it to keep copying and modifying each time when creating new contact?


    return 0;
}