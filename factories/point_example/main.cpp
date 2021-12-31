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

struct Point {
    float x, y;

    // Point(float x, float y) : x{x}, y{y} {}

    // at this point it is Cartesian coordinates
    // and what if I want to initiazie it from polar coordinates

    // Point(float rho, float theta) {
    //     // this wont work cuz the args are same as constructor above, two floats

    // }

    //! \param a this is either x or rho
    //! \param b this is either y or theta
    Point (float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian) {
            x = a;
            y = b;
        } else {
            x = a * cos(b);
            y = a * sin(b);
        }
    }
};

// So far the problem,
// this is what factory is all about
// it's about making sure that the interface to a particular type provides is sensible
// it's understandable, immediately consumable by the client

int main (void)
{


    return 0;
}