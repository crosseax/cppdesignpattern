#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

int main (void)
{
    std::string text = "hello";
    std::string output;

    output += "<p>";
    output += text;
    output += "</p>";

    std::cout << output << std::endl;

    std::string words[] {"hello", "world"};
    std::ostringstream oss;
    oss << "<ul>";
    for (auto w : words) {
        oss << " <li>" << w << "</li>";
    }
    oss << " </ul>";
    std::cout << oss.str() << std::endl;

    // so the idea of the builder desing pattern is that
    // instead of building a string out of these little concatenation
    // you just define some sort of object oriented strcuture 
    // which supports its transformation to a string

    return 0;
}