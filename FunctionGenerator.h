#pragma once

#include "Generator.h"
#include <functional>

namespace miit::algebra
{
    /**
     * @brief Генератор значений с использованием пользовательской функции.
     *
     * Позволяет передать любой алгоритм получения целого числа, например
     * функцию чтения значения с клавиатуры.
     */
    class FunctionGenerator final : public Generator
    {
    private:
        std::function<int()> function;

    public:
        /**
         * @brief Создаёт генератор на основе переданной функции.
         * @param function Функция, возвращающая очередное целое число.
         * @throw std::invalid_argument Если передана пустая функция.
         */
        explicit FunctionGenerator(const std::function<int()> function);

        /**
         * @brief Получает очередное значение вызовом сохранённой функции.
         * @return Целое число, возвращённое пользовательской функцией.
         */
        int generate() override;
    };
}
