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
public:
    // friend class PointFactory; // this violates Open-Close Principle
    Point(float x, float y) : x{x}, y{y} {}


public:
    float x, y;


    friend std::ostream& operator<< (std::ostream& os, const Point& point) {
        os << "x: " << point.x << ", y: " << point.y;
        return os;
    }
};

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