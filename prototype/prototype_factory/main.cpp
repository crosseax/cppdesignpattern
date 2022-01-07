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

    // another approach, copy constructor here
    Address (const Address& other) 
        : street {other.street}, city {other.city}, suite {other.suite} {}

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
        //   address {new Address {other.address->street, other.address->city, other.address->suite}} {}
          address {new Address {*other.address}} {}

    friend std::ostream& operator<< (std::ostream& os, const Contact contact) {
        os << "[Name]: " << contact.name
           << "\n[Address]: " << *contact.address;
        return os;
    }
};

// how to give a prototype of anything?
// one idea is to just make a global variable
Contact main_proto {"", new Address{"123 East Dr", "London", 0}};


// another solution, if you would be more general
// and hide relative things like constructor or so
// then you build a prototype factory
struct EmployeeFactory {
    static std::unique_ptr<Contact> new_main_office_employee (const std::string name, const int suite) {
        static Contact p{"", new Address{"123 East Dr", "London", 0}};
        return new_employee(name, suite, p);
    } 
private:
    static std::unique_ptr<Contact> new_employee (const std::string name, const int suite, const Contact& prototype) {
        auto result = std::make_unique<Contact> (prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};



int main (void)
{
    auto john = EmployeeFactory::new_main_office_employee("John", 123);

    std::cout << *john << std::endl; 

    return 0;
}