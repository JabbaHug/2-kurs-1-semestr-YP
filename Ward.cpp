#include "Ward.h"

Ward::Ward(const int number, const int capacity)
    : number_(number),
      capacity_(capacity)
{
}

void Ward::addPatient(const Patient& patient)
{
    patients_.push_back(patient);
}

int Ward::getNumber() const noexcept
{
    return number_;
}

int Ward::getCapacity() const noexcept
{
    return capacity_;
}

const std::vector<Patient>& Ward::getPatients() const noexcept
{
    return patients_;
}

std::string Ward::toString() const
{
    return "Палата №" + std::to_string(number_)
        + ", вместимость: " + std::to_string(capacity_)
        + ", пациентов: " + std::to_string(patients_.size());
}
