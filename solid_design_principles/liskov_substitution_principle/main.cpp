#include <iostream>

// The goal of this principle is to specify
// that subtypes should be immediately substitutable for their base types


// Basically Liskov Substitution Principle:
// If you have a function which takes a base class
// any derived class hsould be able to be substituted into this function without any problems

// The idea is that when substitute a derived class
// you should be able to substitute it into any location 
// where base class is being used
// so below, the process class is used for base class Rectangle
// but not suitable for derived Square class
// This is then a violation of Liskov Substitution Principle

class Rectangle {
protected:
    int width, height;

public:
    Rectangle(int width, int height) : width {width}, height {height} {}

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }

    virtual void set_width (int width) {
        Rectangle::width = width;
    }

    virtual void set_height (int height) {
        Rectangle::height = height;
    }

    int calc_area() const { 
        return width * height; 
    }
};

class Square : public Rectangle {
public:
    Square(int side) : Rectangle {side, side} {}

    void set_width(int width) override {
        this->width = this->height = width;
    }

    void set_height(int height) override {
        this->width = this->height = height;
    }
};

void process (Rectangle& r) {
    int w = r.get_width();
    r.set_height(10);

    std::cout << "Expected area = " << (w * 10)
              << ", got " << r.calc_area() << std::endl;
}

// you could do
struct RectangleFactory {
    static Rectangle create_rectangle(int width, int height);
    static Rectangle create_square (int side);
};


int main (void)
{
    Rectangle r {3, 4};
    std::cout << r.calc_area() << std::endl;

    process(r);

    Square sq {5};
    process(sq); // when set height to 10, also set width to 10
    // broken the liskov sustitution principle, by broken the setter method


    return 0;
}