#define _USE_MATH_DEFINES // for M_PI_4

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

enum class PointType {
    cartesian,
    polar
};

class Point {
private:
    // unpleasant chagne
    friend class PointFactory; // this violates Open-Close Principle
    // friend class mechanism is hostile to OCP
    // because we have to go into the class already created to redo the change

    // if you dont want to violate OCP
    // you can make everything public, including constructor

    Point(float x, float y) : x{x}, y{y} {}

    
public:
    float x, y;


    friend std::ostream& operator<< (std::ostream& os, const Point& point) {
        os << "x: " << point.x << ", y: " << point.y;
        return os;
    }
};

// Separation of concern
// this is going to be concrete factory, not abstract
// this is how you would implement a factory
// just an ordinary class which contains a couple of methods for the construction of something else
// and it has to be a friend class if you want to access the private member
struct PointFactory {
    static Point NewCartesian(float x, float y) {
        return {x, y};
    }

    static Point NewPolar(float r, float theta) {
        return {r*cos(theta), r*sin(theta)};
    }
};


int main (void)
{
    // You can create a PointFactory
    PointFactory pf;

    // Now you can
    auto p = PointFactory::NewPolar(5, M_PI_4);

    std::cout << "Input(polar coordinates): r = 5, theta = pi/4" << std::endl;
    std::cout << "Output(Cartesian coordinates): " << std::endl;
    std::cout << p << std::endl;

    return 0;
}