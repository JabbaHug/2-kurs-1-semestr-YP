#include "Department.h"

Department::Department(const std::string& name)
    : name_(name)
{
}

const std::string& Department::getName() const noexcept
{
    return name_;
}

std::string Department::toString() const
{
    return name_;
}
