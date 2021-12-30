#include "PersonBuilder.h"

PersonBuilderBase::PersonBuilderBase(Person& person)
    : person{person} {}

PersonBuilder::PersonBuilder()
    : PersonBuilderBase{p} {}