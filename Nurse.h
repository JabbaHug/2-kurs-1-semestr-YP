#pragma once

#include "MedicalWorker.h"

#include <string>

/**
 * @brief Медсестра (средний медицинский персонал).
 *
 * Наследуется от базового класса MedicalWorker.
 */
class Nurse : public MedicalWorker
{
private:
    std::string shift_;

public:
    /**
     * @brief Создаёт медсестру.
     *
     * @param fullName ФИО.
     * @param department Отделение.
     * @param shift Смена (дневная / ночная).
     */
    Nurse(
        const std::string& fullName,
        const std::string& department,
        const std::string& shift);

    /**
     * @brief Возвращает смену.
     *
     * @return Смена.
     */
    const std::string& getShift() const noexcept;

    /**
     * @brief Возвращает строковое представление медсестры.
     *
     * @return Информация о медсестре.
     */
    std::string toString() const override;
};
