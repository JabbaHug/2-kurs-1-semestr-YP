#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 1 варианта 8.
     *
     * Заменяет максимальный элемент каждого столбца нулём.
     */
    class Task1 final : public Exercise<int>
    {
    public:
        /**
         * @brief Создаёт объект задания 1 и заполняет матрицу.
         * @param rows Количество строк матрицы.
         * @param columns Количество столбцов матрицы.
         * @param generator Генератор значений матрицы.
         */
        Task1(const std::size_t rows, const std::size_t columns, Generator& generator);

        /**
         * @brief Выполняет задание 1.
         *
         * В каждом столбце находит максимальный элемент и заменяет
         * все его вхождения нулём.
         */
        void solve() override;
    };
}
