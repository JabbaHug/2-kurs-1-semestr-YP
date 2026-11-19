#include "Task1.h"

namespace miit::algebra
{
    Task1::Task1(const std::size_t rows, const std::size_t columns, const Generator& generator)
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
            int maximum = matrix[0][column];

            for (std::size_t row = 1; row < rowCount; ++row)
            {
                if (matrix[row][column] > maximum)
                {
                    maximum = matrix[row][column];
                }
            }

            for (std::size_t row = 0; row < rowCount; ++row)
            {
                if (matrix[row][column] == maximum)
                {
                    matrix[row][column] = 0;
                }
            }
        }
    }
}
