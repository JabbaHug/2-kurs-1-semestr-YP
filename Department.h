#pragma once

#include <string>

/**
 * @brief Отделение больницы.
 */
class Department
{
private:
    std::string name_;

public:
    /**
     * @brief Создаёт отделение.
     * @param name Название отделения.
     */
    explicit Department(const std::string& name);

    /**
     * @return Название отделения.
     */
    const std::string& getName() const noexcept;

    /**
     * @return Строковое представление отделения.
     */
    std::string toString() const;
};
