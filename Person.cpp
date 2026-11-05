#include "Person.h"

int Person::nextId_ = 1;

Person::Person(const std::string& fullName)
    : fullName_(fullName), id_(nextId_++)
{
}

int Person::getId() const noexcept
{
    return id_;
}

const std::string& Person::getFullName() const noexcept
{
    return fullName_;
}
