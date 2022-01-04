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
    Point(float x, float y) : x{x}, y{y} {}
    float x, y;
    class PointFactory;

public:
    friend std::ostream& operator<< (std::ostream& os, const Point& point) {
        os << "x: " << point.x << ", y: " << point.y;
        return os;
    }

    // There is no hint for the user to use factory
    // Point and PointFactory has no obvious link or connection
    // So people sometimes put the factory inside to give user a hint

    // And this also solve the second problem which is breaking the OCP

    // now for the singleton showcase
    // make a instance of the factory 
    // and expose that instance directly from the point
    static PointFactory Factory;

    // This
    // the inner class have the access of the private member of the outter class
    // so it can use private constructor no problem
private:
    class PointFactory {
        PointFactory() {}
    public:
        static Point NewCartesian(float x, float y) {
            return {x, y};
        }

        static Point NewPolar(float r, float theta) {
            return {r*cos(theta), r*sin(theta)};
        }
    };
};


int main (void)
{
    // Now you can
    // auto p = Point::PointFactory::NewPolar(5, M_PI_4);
    auto p = Point::Factory.NewPolar(5, M_PI_4);

    // you can also do the singleton method, which is going to be covered later

    std::cout << "Input(polar coordinates): r = 5, theta = pi/4" << std::endl;
    std::cout << "Output(Cartesian coordinates): " << std::endl;
    std::cout << p << std::endl;

    return 0;
}