#include <string>
#include <ostream>
#include <iostream>
#include <vector>

class CodeBuilder
{
public:
    CodeBuilder(const std::string& class_name) {
        // todo
    }

    CodeBuilder& add_field(const std::string& name, const std::string& type) {
        // todo
    }

    friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj) {
        os << "class " << 
    }
};


int main (void)
{
    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    std::cout << cb << std::endl;

    // Expected Output
    /*
    class Person {
        std::string name;
        int age;
    };
    */

    return 0;
}