#include "Doctor.h"

#include <sstream>

Doctor::Doctor(
    const std::string& fullName,
    const std::string& department,
    const std::string& specialization,
    const std::vector<Patient>& patients)
    : MedicalWorker(fullName, "Врач", department),
      specialization_(specialization),
      patients_(patients)
{
}

const std::string& Doctor::getSpecialization() const noexcept
{
    return specialization_;
}

const std::vector<Patient>& Doctor::getPatients() const noexcept
{
    return patients_;
}

bool Doctor::observesPatient(const std::string& patientName) const
{
    for (const Patient& current : patients_)
    {
        if (current.getFullName() == patientName)
        {
            return true;
        }
    }

    return false;
}

bool Doctor::observesPatient(const Patient& patient) const
{
    for (const Patient& current : patients_)
    {
        if (current.getId() == patient.getId())
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

    for (std::size_t i = 0; i < patients_.size(); ++i)
    {
        stream << patients_[i].getFullName();

        if (i + 1 < patients_.size())
        {
            stream << ", ";
        }
    }

    return stream.str();
}
