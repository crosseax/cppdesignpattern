#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>



struct Point {
    float x, y;

    Point(float x, float y) : x{x}, y{y} {}

    // at this point it is Cartesian coordinates
    // and what if I want to initiazie it from polar coordinates

    Point(float rho, float theta) {
        // this wont work cuz the args are same as constructor above, two floats

    }
};

int main (void)
{


    return 0;
}