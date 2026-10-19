#include "Doctor.h"

#include <sstream>

Doctor::Doctor(
    const std::string& fullName,
    const std::string& department,
    const std::string& specialization,
    const std::vector<std::string>& patientNames)
    : MedicalWorker(fullName, "Врач", department),
      specialization_(specialization),
      patientNames_(patientNames)
{
}

const std::string& Doctor::getSpecialization() const noexcept
{
    return specialization_;
}

const std::vector<std::string>& Doctor::getPatientNames() const noexcept
{
    return patientNames_;
}

bool Doctor::observesPatient(const std::string& patientName) const
{
    for (const std::string& current : patientNames_)
    {
        if (current == patientName)
        {
            return true;
        }
    }

    return false;
}

std::string Doctor::toString() const
{
    std::ostringstream stream;

    stream << "Врач: " << fullName_
           << ", отделение: " << department_
           << ", специализация: " << specialization_
           << ", пациенты: ";

    for (std::size_t i = 0; i < patientNames_.size(); ++i)
    {
        stream << patientNames_[i];

        if (i + 1 < patientNames_.size())
        {
            stream << ", ";
        }
    }

    return stream.str();
}
