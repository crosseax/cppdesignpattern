#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

struct HtmlBuilder;

// what you would typically do is 
// start creating object oriented structures 
// which represent the different parts of the HTML that you're building
struct HtmlElement {
    // this is a utility class for modeling HTML element in a object oriented way in C++
    std::string name, text;
    std::vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const std::string& name, const std::string& text)
        : name {name}, text {text} {}
    
    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i (indent_size* indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if (text.size() > 0) {
            oss << std::string(indent_size* (indent + 1), ' ') << text << std::endl;
        }
        for (const auto& e : elements) {
            oss << e.str(indent + 1);
        }
        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }

    static HtmlBuilder create(std::string root_name) {
        return {root_name};
    }

    static std::unique_ptr<HtmlBuilder> build2(std::string root_name) {
        return std::make_unique<HtmlBuilder>(root_name);
    }
};

struct HtmlBuilder {
    HtmlElement root;

    HtmlBuilder (std::string root_name) {
        root.name = root_name;
    }

    HtmlBuilder& add_child (std::string child_name, std::string child_text) {
        HtmlElement e {child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    HtmlBuilder* add_child_2 (std::string child_name, std::string child_text) {
        HtmlElement e {child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }

    HtmlElement build() {
        return root;
    }

    std::string str() {
        return root.str();
    }

    operator HtmlElement() const {
        return root;
        // can also do below
        // return std::move(root);
    }
};


int main (void)
{
    std::cout << "===Not Using Builder===" << std::endl;

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

    std::cout << "===Using Fluent Builder===" << std::endl;

    HtmlBuilder builder {"ul"};
    builder.add_child("li", "hello").add_child("li", "world");

    std::cout << builder.str() << std::endl;

    auto builder2 = HtmlElement::create("ul").add_child("li", "another one");
    HtmlElement elem = HtmlElement::create("ul").add_child("li", "another one");
    // HtmlElement elem2 = HtmlElement::create("ul")->add_child_2("li", "another one");

    HtmlElement::create("ul").add_child("once another","try").build();

    return 0;
}