#pragma once
#include "HotDrink.h"
#include "HotDrinkFactory.h"

#include <functional>

// this is a concrete implementation of the abstract factory

class DrinkFactory {
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory() {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name) {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

class DrinkwithVolumeFactory {
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
    DrinkwithVolumeFactory() {
        factories["tea"] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
        // this lambda is the factory method
        // it's just encapsulated as standalone function
    }

    std::unique_ptr<HotDrink> make_drink (const std::string& name) {
        return factories[name]();
    }

    // now this way you end up with a functional factory 
    // as opposite to an abstract factory that's based on inheritance
};