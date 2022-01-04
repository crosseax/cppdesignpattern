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
    Point(float x, float y) : x{x}, y{y} {}

public:
    float x, y;

    // This implementation below is called a Factory method
    // Essentially, you have these static methods
    // which allow you to construct a particular object and they use private constructor
    // So when you return {}, 
    // you are essentailly returning point with {} in C++
    // so like 
    // return Point {x, y};
    static Point NewCartesian(float x, float y) {
        return {x, y};
    }

    static Point NewPolar(float r, float theta) {
        return {r*cos(theta), r*sin(theta)};
    }

    friend std::ostream& operator<< (std::ostream& os, const Point& point) {
        os << "x: " << point.x << ", y: " << point.y;
        return os;
    }
};


int main (void)
{
    // Now what you can do:
    auto p = Point::NewPolar(5, M_PI_4);

    std::cout << "Input(polar coordinates): r = 5, theta = pi/4" << std::endl;
    std::cout << "Output(Cartesian coordinates): " << std::endl;
    std::cout << p << std::endl;

    return 0;
}