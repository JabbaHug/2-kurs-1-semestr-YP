#pragma once

#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
     * @brief Генератор случайных целых чисел.
     *
     * Наследуется от Generator и возвращает значения из заданного диапазона.
     */
    class RandomGenerator final : public Generator
    {
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 engine;

    public:
        /**
         * @brief Создаёт генератор случайных чисел.
         * @param minValue Минимально возможное значение.
         * @param maxValue Максимально возможное значение.
         */
        RandomGenerator(const int minValue, const int maxValue);

        /**
         * @brief Генерирует случайное целое число.
         * @return Случайное число из заданного диапазона.
         */
        int generate() override;
    };
}
