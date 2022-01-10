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

    Address() {}

    Address (const std::string& street, const std::string& city, int suite)
        : street {street}, city {city}, suite{suite} {}

    Address (const Address& other) 
        : street {other.street}, city {other.city}, suite {other.suite} {}

    friend std::ostream& operator<< (std::ostream& os, const Address& address) {
        os << "Street: " << address.street 
           << "; City: " << address.city
           << "; Suite: " << address.suite;
        return os;
    }

private:
    friend class boost::serialization::access;

    template <class archive>
    void serialize(archive& ar, const unsigned version) {
        ar & street;
        ar & city;
        ar & suite; // boost::serialization knows about all the different data types
    }
};

struct Contact {
    std::string name;
    Address* address;

    Contact() {}

    Contact (const std::string& name, Address* address) 
        : name {name}, address {address} {}

    ~Contact() { delete address; }


    Contact (const Contact& other) 
        : name {other.name}, 
          address {new Address {*other.address}} {}

    friend std::ostream& operator<< (std::ostream& os, const Contact contact) {
        os << "[Name]: " << contact.name
           << "\n[Address]: " << *contact.address;
        return os;
    }

private:
    friend class boost::serialization::access;

    template <class archive>
    void serialize(archive& ar, const unsigned version) {
        ar & name;
        ar & address;
    }
};

Contact main_proto {"", new Address{"123 East Dr", "London", 0}};


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
    auto clone = [](const Contact& c) {
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;
        std::string s = oss.str();
        std::cout << s << std::endl;

        std::istringstream iss(s);
        boost::archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };

    auto john = EmployeeFactory::new_main_office_employee("john", 123);
    auto jane = clone(*john);

    jane.name = "Jane";

    std::cout << *john << std::endl << jane << std::endl;


    return 0;
}