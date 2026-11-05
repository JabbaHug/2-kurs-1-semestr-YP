#include "Nurse.h"

#include <sstream>

Nurse::Nurse(
    const std::string& fullName,
    const std::string& department,
    const std::string& shift)
    : MedicalWorker(fullName, "Медсестра", department),
      shift_(shift)
{
}

const std::string& Nurse::getShift() const noexcept
{
    return shift_;
}

std::string Nurse::toString() const
{
    std::ostringstream stream;

    stream << "Медсестра: " << fullName_
           << ", отделение: " << department_
           << ", смена: " << shift_;

    return stream.str();
}
