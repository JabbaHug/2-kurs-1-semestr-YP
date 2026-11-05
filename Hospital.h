#pragma once

#include "Department.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Ward.h"

#include <functional>
#include <string>
#include <utility>
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
    std::vector<Doctor> doctors_;
    std::vector<Nurse> nurses_;
    std::vector<std::pair<bool, std::size_t>> workerOrder_;

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
     * @brief Добавляет врача в больницу.
     * @param doctor Добавляемый врач.
     */
    void addWorker(const Doctor& doctor);

    /**
     * @brief Добавляет медсестру в больницу.
     * @param nurse Добавляемая медсестра.
     */
    void addWorker(const Nurse& nurse);

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
     * @return Коллекция ссылок на работников как на MedicalWorker.
     */
    std::vector<std::reference_wrapper<const MedicalWorker>> getWorkers() const;

    /**
     * @return Сводная информация о больнице.
     */
    std::string toString() const;
};
