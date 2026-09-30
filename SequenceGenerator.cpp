#include "SequenceGenerator.h"
#include <stdexcept>
#include <utility>

namespace miit::algebra
{
    SequenceGenerator::SequenceGenerator(const std::vector<int> values)
        : values(std::move(values))
    {
    }

    int SequenceGenerator::generate()
    {
        if (position >= values.size())
        {
            throw std::out_of_range("SequenceGenerator has no more values");
        }

        return values[position++];
    }
}
