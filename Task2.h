#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 2 варианта 8.
     *
     * Вставляет после всех строк, содержащих максимальный по модулю
     * элемент массива, первую строку.
     */
    class Task2 final : public Exercise<int>
    {
    public:
        /**
         * @brief Создаёт объект задания 2 и заполняет матрицу.
         * @param rows Количество строк матрицы.
         * @param columns Количество столбцов матрицы.
         * @param generator Генератор значений матрицы.
         */
        Task2(const std::size_t rows, const std::size_t columns, Generator& generator);

        /**
         * @brief Выполняет задание 2.
         *
         * Находит максимальный по модулю элемент матрицы и после каждой
         * строки, содержащей такой элемент, вставляет копию первой строки.
         */
        void solve() override;
    };
}
