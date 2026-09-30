#pragma once

#include "Generator.h"
#include <vector>
#include <cstddef>

namespace miit::algebra
{
    /**
     * @brief Генератор последовательности заранее заданных чисел.
     *
     * Используется в основном для воспроизводимого заполнения матриц
     * и модульного тестирования.
     */
    class SequenceGenerator final : public Generator
    {
    private:
        std::vector<int> values;
        std::size_t position = 0;

    public:
        /**
         * @brief Создаёт генератор из последовательности значений.
         * @param values Набор целых чисел для последовательной выдачи.
         */
        explicit SequenceGenerator(const std::vector<int> values);

        /**
         * @brief Возвращает следующее значение последовательности.
         * @return Следующее целое число.
         * @throw std::out_of_range Если все значения уже выданы.
         */
        int generate() override;
    };
}
