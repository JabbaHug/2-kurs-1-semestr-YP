#include "Patient.h"

Patient::Patient(
    const std::string& fullName,
    const std::string& diagnosis,
    const int wardNumber)
    : fullName_(fullName),
      diagnosis_(diagnosis),
      wardNumber_(wardNumber)
{
}

const std::string& Patient::getFullName() const noexcept
{
    return fullName_;
}

const std::string& Patient::getDiagnosis() const noexcept
{
    return diagnosis_;
}

int Patient::getWardNumber() const noexcept
{
    return wardNumber_;
}

std::string Patient::toString() const
{
    return fullName_
        + ", диагноз: " + diagnosis_
        + ", палата: " + std::to_string(wardNumber_);
}
