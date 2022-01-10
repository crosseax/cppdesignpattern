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

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

// Serialization and Deserialization
// when you serialize something, you want to store all the aspects of an object
// when you deserialize, you want to restore all the aspects of an object

struct Contact {
    std::string name;
    // the problem is here with the pointer again
    // we dont want to save just the pointer value
    // we want to save what the pointer points to
    Address* address;

    Contact() = default;

    Contact (const std::string& name, Address* address) 
        : name {name}, address {address} {}

    // a solution, for deep copy instead of shallow copy
    // is copy constructor

    Contact (const Contact& other) 
        : name {other.name}, 
        //   address {new Address {other.address->street, other.address->city, other.address->suite}} {}
          address {new Address {*other.address}} {}

    ~Contact() { delete address; }

    friend std::ostream& operator<< (std::ostream& os, const Contact contact) {
        os << "[Name]: " << contact.name
           << "\n[Address]: " << *contact.address;
        return os;
    }

private:
    // giving boost access of this class
    friend class boost::serialization::access;

    // you can either spilt the serialization into the saving and loading if you want the logic to be different
    // or you can just have a single function which kind of takes care of both of these
    template <class archive>
    void serialize(archive& ar, const unsigned version) {
        ar & name; // using the ampersand operator& to define the parts we serialize
        ar & address; // we dont have to dereference the pointer, it knows if it's a pointer, we have to follow it to serialize what we interested in
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
    // Contact john {"John Doe", new Address{"123 East Dr", "London", 123}};
    // // so here, john is acting like a prototype,
    // // and we replicate the prototype using copy constructor
    // // then customize the copied instance
    
    // Contact jane{john};
    // // or Contact jane = john;
    

    // jane.name = "Jane Smith";
    // jane.address->suite = 103;

    // std::cout << john << std::endl;
    // std::cout << jane << std::endl;
    // std::cout << "Issue: Outputing memory address instead of values" << std::endl;
    // std::cout << "Issue: Changing the Copy also changes the original" << std::endl;

    auto clone = [](const Contact& c) {
        // first serialize it to string
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;
        std::string s = oss.str();
        std::cout << s << std::endl;

        // then deserialize it into a new object
        std::istringstream iss(s);
        boost::archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };


    return 0;
}