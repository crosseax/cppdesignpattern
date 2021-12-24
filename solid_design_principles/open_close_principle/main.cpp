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

    std::vector<Product*> by_color(std::vector<Product*> items, const Color color) {
        std::vector<Product*> result;
        for (auto& i : items) {
            if (i->color == color) {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<Product*> by_size(std::vector<Product*> items, const Size size) {
        std::vector<Product*> result;
        for (auto& i : items) {
            if (i->size == size) {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<Product*> by_size_and_color(std::vector<Product*> items, const Size size, const Color color) {
        std::vector<Product*> result;
        for (auto& i : items) {
            if (i->size == size && i->color == color) {
                result.push_back(i);
            }
        }
        return result;
    }
};

// acts like a prototype
template <typename T> struct AndSpecification;
template <typename T> 
struct Specification {
    virtual ~Specification() = default;
    virtual bool is_satisfied(T* item) = 0;

    // overload && operator for better/shorter code in main
    AndSpecification<T> operator&& (Specification<T>&& other) {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T> 
struct Filter {
    virtual ~Filter() = default;
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

template <typename T>
struct AndSpecification : Specification<T> {
    Specification<T>& first;
    Specification<T>& second;
    
    AndSpecification (Specification<T>& first, Specification<T>& second)
        : first {first}, second {second} {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
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
        std::cout << "[Filter] " << item->name << " is green" << std::endl;
    }
    
    std::vector<Product*> large_things = pf.by_size(items, Size::large);
    for (auto& item : large_things) {
        std::cout << "[Filter] " << item->name << " is large" << std::endl;
    }

    std::vector<Product*> green_and_large_things = pf.by_size_and_color(items, Size::large, Color::green);
    for (auto& item : green_and_large_things) {
        std::cout << "[Filter] " << item->name << " is green and large" << std::endl;
    }



    std::cout << std::endl;



    BetterFilter bf;

    ColorSpecification green (Color::green);
    for (auto& item : bf.filter(items, green)) {
        std::cout << "[BetterFilter] " << item->name << " is green" << std::endl;
    }

    SizeSpecification large (Size::large);
    for (auto& item : bf.filter(items, large)) {
        std::cout << "[BetterFilter] " << item->name << " is large" << std::endl;
    }

    AndSpecification<Product> green_and_large (green, large);
    for (auto& item : bf.filter(items, green_and_large)) {
        std::cout << "[BetterFilter] " << item->name << " is green and large" << std::endl;
    }



    std::cout << std::endl;



    auto specs = ColorSpecification(Color::green) && SizeSpecification(Size::large);
    for (auto& item : bf.filter(items, specs)) {
        std::cout << "[BetterFilter && overload] " << item->name << " is green and large" << std::endl;
    }

    return 0;
}