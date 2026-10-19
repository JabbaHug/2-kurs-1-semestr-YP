#pragma once

#include "Department.h"
#include "MedicalWorker.h"
#include "Ward.h"

#include <memory>
#include <string>
#include <vector>

/**
 * @brief Больница.
 *
 * Содержит отделения, палаты и медицинских работников.
 * Пациенты хранятся внутри палат.
 */
class Hospital
{
private:
    std::string name_;

    std::vector<Department> departments_;
    std::vector<Ward> wards_;
    std::vector<std::unique_ptr<MedicalWorker>> workers_;

public:
    /**
     * @brief Создаёт больницу.
     * @param name Название больницы.
     */
    explicit Hospital(const std::string& name);

    /**
     * @brief Добавляет отделение.
     * @param department Добавляемое отделение.
     */
    void addDepartment(const Department& department);

    /**
     * @brief Добавляет палату вместе с её пациентами.
     * @param ward Палата. В больнице сохраняется её копия.
     */
    void addWard(const Ward& ward);

    /**
     * @brief Добавляет работника и принимает владение им.
     * @param worker Умный указатель на медицинского работника.
     * @throws std::invalid_argument Если указатель пустой.
     */
    void addWorker(std::unique_ptr<MedicalWorker> worker);

    /**
     * @return Название больницы.
     */
    const std::string& getName() const noexcept;

    /**
     * @return Отделения больницы.
     */
    const std::vector<Department>& getDepartments() const noexcept;

    /**
     * @return Палаты больницы.
     */
    const std::vector<Ward>& getWards() const noexcept;

    /**
     * @return Коллекция работников базового типа MedicalWorker.
     */
    const std::vector<std::unique_ptr<MedicalWorker>>&
        getWorkers() const noexcept;

    /**
     * @return Сводная информация о больнице.
     */
    std::string toString() const;
};
