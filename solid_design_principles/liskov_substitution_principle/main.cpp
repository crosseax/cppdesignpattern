#include <iostream>

// The goal of this principle is to specify
// that subtypes should be immediately substitutable for their base types

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


int main (void)
{
    Rectangle r {3, 4};
    std::cout << r.calc_area() << std::endl;

    process(r);


    return 0;
}