#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create() {
    return PersonBuilder();
}

std::ostream& operator<< (std::ostream& os, Person& person) {
    return os
       << "Street address: " << person.street_address << "\n"
       << "Postcode: " << person.post_code << "\n"
       << "City: " << person.city << "\n"
       << "Company name: " << person.company_name << "\n"
       << "Position: " << person.position << "\n"
       << "Annual Income: " << person.annual_income << "\n";
    
}