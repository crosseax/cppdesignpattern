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

    friend std::ostream& operator<< (std::ostream& os, const Address& address) {
        os << "Street: " << address.street 
           << "; City: " << address.city
           << "; Suite: " << address.suite;
        return os;
    }
};

struct Contact {
    std::string name;
    Address address;

    Contact (const std::string& name, const Address& address) 
        : name {name}, address {address} {}

    friend std::ostream& operator<< (std::ostream& os, const Contact contact) {
        os << "[Name]: " << contact.name
           << "\n[Address]: " << contact.address;
        return os;
    }
};

// but in real cases, people usually use pointer instead of strings
struct Contact2 {
    std::string name;
    Address* address;

    Contact2 (const std::string& name, Address* address) 
        : name {name}, address {address} {}

    // problems: 
        // who owns the pointer and who deletes it

    friend std::ostream& operator<< (std::ostream& os, const Contact2 contact2) {
        os << "[Name]: " << contact2.name
           << "\n[Address]: " << *contact2.address;
        return os;
    }
};



int main (void)
{
    Contact john {"John Doe", Address{"123 East Dr", "London", 123}};
    // Contact jane {"Jane Smith", Address{"123 East Dr", "London", 103}};
    // is it really worth it to keep copying and modifying each time when creating new contact?

    // what you can also do
    Contact jane = john;
    jane.name = "Jane Smith";
    jane.address.suite = 103;

    std::cout << john << std::endl;
    std::cout << jane << std::endl;

    std::cout << std::endl;

    Contact2 john2 {"John2 Doe", new Address{"123 East Dr", "London", 123}};
    Contact2 jane2 = john2; // you are copying the pointer value, so this is a shallow copy
    jane2.name = "Jane2 Smith";
    jane2.address->suite = 103;

    std::cout << john2 << std::endl;
    std::cout << jane2 << std::endl;
    std::cout << "Issue: Outputing memory address instead of values" << std::endl;
    std::cout << "Issue2: Changing the Copy also changes the original" << std::endl;

    return 0;
}