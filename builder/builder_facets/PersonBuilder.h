#pragma once

#include "Person.h"

class PersonBuilderBase {
protected:
    Person& person;
public:
    PersonBuilderBase(Person& person);
};

class PersonBuilder : PersonBuilderBase{
private:
    Person p;
public:
    PersonBuilder();
};