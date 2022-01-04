#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

// abstract factories
// families of factories which use inheritance 
// to polymorphically call the different factory

std::unique_ptr<HotDrink> make_drink (std::string type) {
    std::unique_ptr<HotDrink> drink;
    if (type == "tea") {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = std::make_unique<Coffee>();
        drink->prepare(200);
    }
    return drink;
}

int main (void)
{
    // this works, but not using the abstract factory
    make_drink("tea");


    // from now on, using abstract factory
    DrinkFactory df;
    auto c = df.make_drink("coffee");


    return 0;
}