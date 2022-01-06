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
    Address* address;

    Contact (const std::string& name, Address* address) 
        : name {name}, address {address} {}

    // a solution, for deep copy instead of shallow copy
    // is copy constructor

    Contact (const Contact& other) 
        : name {other.name}, 
          address {new Address {other.address->street, other.address->city, other.address->suite}} {}

    friend std::ostream& operator<< (std::ostream& os, const Contact contact) {
        os << "[Name]: " << contact.name
           << "\n[Address]: " << *contact.address;
        return os;
    }
};



int main (void)
{
    Contact john {"John Doe", new Address{"123 East Dr", "London", 123}};
    Contact jane{john};
    // or Contact jane = john;
    

    jane.name = "Jane Smith";
    jane.address->suite = 103;

    std::cout << john << std::endl;
    std::cout << jane << std::endl;
    std::cout << "Issue: Outputing memory address instead of values" << std::endl;
    std::cout << "Issue: Changing the Copy also changes the original" << std::endl;

    return 0;
}