#include "Hospital.h"

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

void Hospital::addWorker(const Doctor& doctor)
{
    doctors_.push_back(doctor);
    workerOrder_.emplace_back(true, doctors_.size() - 1);
}

void Hospital::addWorker(const Nurse& nurse)
{
    nurses_.push_back(nurse);
    workerOrder_.emplace_back(false, nurses_.size() - 1);
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

std::vector<std::reference_wrapper<const MedicalWorker>>
Hospital::getWorkers() const
{
    std::vector<std::reference_wrapper<const MedicalWorker>> result;
    result.reserve(workerOrder_.size());

    for (const auto& worker : workerOrder_)
    {
        if (worker.first)
        {
            result.emplace_back(doctors_[worker.second]);
        }
        else
        {
            result.emplace_back(nurses_[worker.second]);
        }
    }

    return result;
}

std::string Hospital::toString() const
{
    return name_
        + ", работников: " + std::to_string(workerOrder_.size())
        + ", палат: " + std::to_string(wards_.size());
}
