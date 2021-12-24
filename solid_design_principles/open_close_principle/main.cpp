#include <iostream>
#include <vector>
#include <string>

// code should be open for extension
// and close for modification

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

struct ProductFilter {

    // This works, but doesnt scale
    // if have n criteria, then 2^n-1 functions
    // we are modifying existing code, and this isn't great

    std::vector<Product*> by_color(std::vector<Product*> items, Color color) {
        std::vector<Product*> result;
        for (auto& i : items) {
            if (i->color == color) {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<Product*> by_size(std::vector<Product*> items, Size size) {
        std::vector<Product*> result;
        for (auto& i : items) {
            if (i->size == size) {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<Product*> by_size_and_color(std::vector<Product*> items, Size size, Color color) {
        std::vector<Product*> result;
        for (auto& i : items) {
            if (i->size == size && i->color == color) {
                result.push_back(i);
            }
        }
        return result;
    }
};

template <typename T> 
struct Specification {
    virtual bool is_satisfied(T* item) = 0;
};

template <typename T> 
struct Filter {
    virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
    std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) override {
        std::vector<Product*> result;
        for (auto& item : items) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;
    ColorSpecification(const Color color) : color {color} {}
    bool is_satisfied(Product* item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;
    SizeSpecification(const Size size) : size {size} {}
    bool is_satisfied(Product* item) override {
        return item->size == size;
    }
};

int main (void)
{
    Product apple {"Apple", Color::green, Size::small};
    Product tree {"Tree", Color::green, Size::large};
    Product house {"House", Color::blue, Size::large};

    std::vector<Product*> items { &apple, &tree, &house };
    
    ProductFilter pf;

    std::vector<Product*> green_things = pf.by_color(items, Color::green);
    for (auto& item : green_things) {
        std::cout << item->name << " is green" << std::endl;
    }
    
    std::vector<Product*> large_things = pf.by_size(items, Size::large);
    for (auto& item : large_things) {
        std::cout << item->name << " is large" << std::endl;
    }

    std::vector<Product*> green_and_large_things = pf.by_size_and_color(items, Size::large, Color::green);
    for (auto& item : green_and_large_things) {
        std::cout << item->name << " is green and large" << std::endl;
    }
    

    std::cout << std::endl;

    BetterFilter bf;
    ColorSpecification green (Color::green);
    
    for (auto& item : bf.filter(items, green)) {
        std::cout << item->name << " is green using better filter" << std::endl;
    }

    return 0;
}