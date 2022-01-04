#pragma once
#include <iostream>
#include <memory>
#include <map>

struct HotDrink {
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
    void prepare(int volume) override {
        std::cout << "Take a tea bad, boill water, pour " << volume << "ml, add some lemon\n";
    }
};

struct Coffee : HotDrink {
    void prepare(int volume) override {
        std::cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy\n";
    }
};