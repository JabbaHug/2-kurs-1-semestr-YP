#include "FunctionGenerator.h"
#include <stdexcept>
#include <utility>

namespace miit::algebra
{
    FunctionGenerator::FunctionGenerator(const std::function<int()> function)
        : function(std::move(function))
    {
        if (!this->function)
        {
            throw std::invalid_argument("Generator function is empty");
        }
    }

    int FunctionGenerator::generate()
    {
        return function();
    }
}
