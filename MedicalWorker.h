#pragma once

#include <string>

/**
 * @brief Базовый класс медицинского работника больницы.
 *
 * Содержит общую информацию о сотрудниках:
 * врачах и среднем медицинском персонале.
 */
class MedicalWorker
{
protected:
    std::string fullName_;
    std::string position_;
    std::string department_;

public:
    /**
     * @brief Создаёт медицинского работника.
     *
     * @param fullName ФИО работника.
     * @param position Должность.
     * @param department Отделение больницы.
     */
    MedicalWorker(
        const std::string& fullName,
        const std::string& position,
        const std::string& department);

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~MedicalWorker() = default;

    /**
     * @brief Возвращает ФИО работника.
     *
     * @return ФИО.
     */
    const std::string& getFullName() const noexcept;

    /**
     * @brief Возвращает должность.
     *
     * @return Должность.
     */
    const std::string& getPosition() const noexcept;

    /**
     * @brief Возвращает отделение.
     *
     * @return Название отделения.
     */
    const std::string& getDepartment() const noexcept;

    /**
     * @brief Выводит информацию о работнике в строковом виде.
     *
     * @return Информация о работнике.
     */
    virtual std::string toString() const = 0;
};
