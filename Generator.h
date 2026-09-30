#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный генератор целочисленных значений.
     *
     * Базовый класс для алгоритмов заполнения матрицы.
     */
    class Generator
    {
    public:
        /**
         * @brief Виртуальный деструктор генератора.
         */
        virtual ~Generator() = default;

        /**
         * @brief Генерирует очередное целочисленное значение.
         * @return Сгенерированное целое число.
         */
        virtual int generate() = 0;
    };
}
