#include "Task1.h"
#include <stdexcept>

namespace miit::algebra
{
    Task1::Task1(const std::size_t rows, const std::size_t columns, Generator& generator)
        : Exercise<int>(rows, columns, generator)
    {
    }

    void Task1::solve()
    {
        if (matrix.empty())
        {
            return;
        }

        const std::size_t rowCount = matrix.rows();
        const std::size_t columnCount = matrix.columns();

        for (std::size_t column = 0; column < columnCount; ++column)
        {
            int maximum = matrix[column];

            for (std::size_t row = 1; row < rowCount; ++row)
            {
                const int value = matrix[row * columnCount + column];
                if (value > maximum)
                {
                    maximum = value;
                }
            }

            for (std::size_t row = 0; row < rowCount; ++row)
            {
                if (matrix[row * columnCount + column] == maximum)
                {
                    matrix[row * columnCount + column] = 0;
                }
            }
        }
    }
}
