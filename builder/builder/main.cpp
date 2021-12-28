#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

// what you would typically do is 
// start creating object oriented structures 
// which represent the different parts of the HTML that you're building



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

    std::cout << std::endl;

    return 0;
}