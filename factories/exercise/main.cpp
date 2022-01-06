#include <string>
#include <iostream>


struct Person
{
  int id;
  std::string name;
};

class PersonFactory
{
public:
  Person create_person(const std::string& name)
  {
    // todo
  }
};