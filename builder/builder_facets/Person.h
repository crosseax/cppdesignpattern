#pragma once

#include <string>

class PersonBuilder;

class Person {
    // address info
    std::string street_address, post_code, city;

    // employment
    std::string company_name, position;
    int annual_income{0};

    Person(){
        std::cout << "Person created\n";
    }

public:
    ~Person() {
        std::cout << "Person destroyed\n";
    }

    static PersonBuilder create();

    Person(Person&& other)
        : street_address{move(other.street_address)},
        post_code{move(other.post_code)},
        city{move(other.city)},
        company_name{move(other.company_name)},
        position{move(other.position)},
        annual_income{other.annual_income}
    {
    }

    Person& operator=(Person&& other) {
        if (this == &other)
        return *this;
        street_address = move(other.street_address);
        post_code = move(other.post_code);
        city = move(other.city);
        company_name = move(other.company_name);
        position = move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& os, Person& person);


    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};