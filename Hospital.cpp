#include "Hospital.h"

#include <stdexcept>
#include <utility>

Hospital::Hospital(const std::string& name)
    : name_(name)
{
}

void Hospital::addDepartment(const Department& department)
{
    departments_.push_back(department);
}

void Hospital::addWard(const Ward& ward)
{
    wards_.push_back(ward);
}

void Hospital::addWorker(std::unique_ptr<MedicalWorker> worker)
{
    if (worker == nullptr)
    {
        throw std::invalid_argument("Работник не задан.");
    }

    workers_.push_back(std::move(worker));
}

const std::string& Hospital::getName() const noexcept
{
    return name_;
}

const std::vector<Department>&
Hospital::getDepartments() const noexcept
{
    return departments_;
}

const std::vector<Ward>& Hospital::getWards() const noexcept
{
    return wards_;
}

const std::vector<std::unique_ptr<MedicalWorker>>&
Hospital::getWorkers() const noexcept
{
    return workers_;
}

std::string Hospital::toString() const
{
    return name_
        + ", работников: " + std::to_string(workers_.size())
        + ", палат: " + std::to_string(wards_.size());
}
