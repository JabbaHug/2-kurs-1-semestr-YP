#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Класс реализации Задания №2 для Варианта 14.
     * 
     * Бизнес-логика: Вставить после всех столбцов, содержащих нулевой элемент, первый столбец.
     */
    class Task2 final : public Exercise<int>
    {
    public:
        /**
         * @brief Конструктор задачи №2.
         * @param rows Число строк матрицы.
         * @param columns Число столбцов матрицы.
         * @param generator Генератор для первичного наполнения.
         */
        Task2(std::size_t rows, std::size_t columns, Generator& generator);

        /**
         * @brief Выполняет алгоритм поиска нулей и дублирования первого столбца.
         */
        void solve() override;
    };
}
