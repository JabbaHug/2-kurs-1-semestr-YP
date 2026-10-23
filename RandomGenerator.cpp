#include "RandomGenerator.h"

namespace miit::algebra
{
    RandomGenerator::RandomGenerator(const int minValue, const int maxValue)
        : distribution(minValue, maxValue),
          engine(std::random_device{}())
    {
    }

    int RandomGenerator::generate() const
    {
        return distribution(engine);
    }
}
