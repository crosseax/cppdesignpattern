#include <string>
#include <ostream>
#include <iostream>
using namespace std;

class CodeBuilder
{
public:
    CodeBuilder(const string& class_name) {
        // todo
    }

    CodeBuilder& add_field(const string& name, const string& type) {
        // todo
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj) {

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