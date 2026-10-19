#pragma once

#include "MedicalWorker.h"

#include <string>
#include <vector>

/**
 * @brief Врач больницы.
 *
 * Наследуется от базового класса MedicalWorker.
 * Хранит специализацию и список наблюдаемых пациентов.
 */
class Doctor : public MedicalWorker
{
private:
    std::string specialization_;
    std::vector<std::string> patientNames_;

public:
    /**
     * @brief Создаёт врача.
     *
     * @param fullName ФИО врача.
     * @param department Отделение.
     * @param specialization Специализация врача.
     * @param patientNames ФИО наблюдаемых пациентов.
     */
    Doctor(
        const std::string& fullName,
        const std::string& department,
        const std::string& specialization,
        const std::vector<std::string>& patientNames);

    /**
     * @brief Возвращает специализацию.
     *
     * @return Специализация.
     */
    const std::string& getSpecialization() const noexcept;

    /**
     * @brief Возвращает список пациентов.
     *
     * @return ФИО пациентов.
     */
    const std::vector<std::string>& getPatientNames() const noexcept;

    /**
     * @brief Проверяет, наблюдает ли врач указанного пациента.
     *
     * @param patientName ФИО пациента.
     * @return true, если пациент есть в списке.
     */
    bool observesPatient(const std::string& patientName) const;

    /**
     * @brief Возвращает строковое представление врача.
     *
     * @return Информация о враче.
     */
    std::string toString() const override;
};
