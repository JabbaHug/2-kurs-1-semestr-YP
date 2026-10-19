#include "MedicalWorker.h"

MedicalWorker::MedicalWorker(
    const std::string& fullName,
    const std::string& position,
    const std::string& department)
    : fullName_(fullName),
      position_(position),
      department_(department)
{
}

const std::string& MedicalWorker::getFullName() const noexcept
{
    return fullName_;
}

const std::string& MedicalWorker::getPosition() const noexcept
{
    return position_;
}

const std::string& MedicalWorker::getDepartment() const noexcept
{
    return department_;
}
