#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

// It's the thing about the object being so complicated 
// that you need separate builders for several different aspects 
// of that particular object
// So this is called a Builder Facet (pronounce fa-sah)



int main (void)
{
    Person p = Person::create()
        .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
        .works().at("PragmaSoft").as_a("Consultant").earning(10e6);

    std::cout << p << std::endl;
    
    return 0;
}