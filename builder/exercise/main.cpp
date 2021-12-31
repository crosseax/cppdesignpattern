#include <string>
#include <ostream>
#include <iostream>
#include <vector>

struct Field {
    std::string name, type;
    
    Field (const std::string& name, const std::string& type) 
        : name {name}, type {type} {}

    friend std::ostream& operator<< (std::ostream& os, const Field& obj) {
        return os << obj.type << " " << obj.name << ";" ;
    }
};

struct Class {
    std::string name;
    std::vector<Field> fields;

    friend std::ostream& operator<<(std::ostream& os, const Class& obj) {
        os << "class " << obj.name << "\n{\n";
        for (auto&& field : obj.fields) {
            os << "  " << field << "\n";
        }
        return os << "};\n";
    }
};

class CodeBuilder {
    Class the_class;
public:
    CodeBuilder(const std::string& class_name) {
        the_class.name = class_name;
    }

    CodeBuilder& add_field(const std::string& name, const std::string& type) {
        the_class.fields.emplace_back(Field{name, type});
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj) {
        return os << obj.the_class;
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