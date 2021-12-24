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

    return 0;
}