#pragma once

#include <string>

/**
 * @brief Пациент больницы.
 */
class Patient
{
private:
    std::string fullName_;
    std::string diagnosis_;
    int wardNumber_;

public:
    /**
     * @brief Создаёт пациента.
     * @param fullName ФИО пациента.
     * @param diagnosis Диагноз.
     * @param wardNumber Номер палаты.
     */
    Patient(
        const std::string& fullName,
        const std::string& diagnosis,
        const int wardNumber);

    /**
     * @return ФИО пациента.
     */
    const std::string& getFullName() const noexcept;

    /**
     * @return Диагноз.
     */
    const std::string& getDiagnosis() const noexcept;

    /**
     * @return Номер палаты.
     */
    int getWardNumber() const noexcept;

    /**
     * @return Информация о пациенте.
     */
    std::string toString() const;
};
