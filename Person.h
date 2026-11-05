#pragma once

#include <string>

/**
 * @brief Абстрактный базовый класс человека с уникальным ID.
 */
class Person
{
protected:
    std::string fullName_;

private:
    static int nextId_;
    int id_;

public:
    /**
     * @brief Создаёт человека с новым уникальным ID.
     * @param fullName ФИО человека.
     */
    explicit Person(const std::string& fullName);

    virtual ~Person() = default;

    /**
     * @return Уникальный ID человека.
     */
    int getId() const noexcept;

    /**
     * @return ФИО человека.
     */
    const std::string& getFullName() const noexcept;

    /**
     * @return Информация о человеке.
     */
    virtual std::string toString() const = 0;
};
