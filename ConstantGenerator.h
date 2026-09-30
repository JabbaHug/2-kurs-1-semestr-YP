#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /** @brief Генератор, возвращающий одно постоянное значение. */
    class ConstantGenerator final : public Generator
    {
    private:
        const int value;
    public:
        /** @brief Создаёт генератор постоянного значения. @param value Значение. */
        explicit ConstantGenerator(const int value);
        /** @brief Возвращает постоянное значение. @return Значение генератора. */
        int generate() override;
    };
}
