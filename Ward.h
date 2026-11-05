#pragma once

#include "Patient.h"

#include <string>
#include <vector>

/**
 * @brief Палата больницы.
 *
 * Хранит номер, вместимость и список пациентов.
 */
class Ward
{
private:
    int number_;
    int capacity_;
    std::vector<Patient> patients_;

public:
    /**
     * @brief Создаёт палату.
     * @param number Номер палаты.
     * @param capacity Вместимость.
     */
    Ward(const int number, const int capacity);

    /**
     * @brief Добавляет пациента в палату.
     * @param patient Пациент. В палате сохраняется его копия.
     */
    void addPatient(const Patient& patient);

    /**
     * @return Номер палаты.
     */
    int getNumber() const noexcept;

    /**
     * @return Вместимость палаты.
     */
    int getCapacity() const noexcept;

    /**
     * @return Список пациентов палаты.
     */
    const std::vector<Patient>& getPatients() const noexcept;

    /**
     * @return Информация о палате.
     */
    std::string toString() const;
};
