#include "Task2.h"
#include <cstdlib>
#include <vector>

namespace miit::algebra
{
    Task2::Task2(const std::size_t rows, const std::size_t columns, const Generator& generator)
        : Exercise<int>(rows, columns, generator)
    {
    }

    void Task2::solve()
    {
        if (matrix.rows() == 0 || matrix.columns() == 0)
        {
            return;
        }

        const std::size_t rowCount = matrix.rows();
        const std::size_t columnCount = matrix.columns();

        int maximumByAbsoluteValue = 0;
        for (std::size_t index = 0; index < rowCount * columnCount; ++index)
        {
            const int absolute = std::abs(matrix[index]);
            if (absolute > maximumByAbsoluteValue)
            {
                maximumByAbsoluteValue = absolute;
            }
        }

        std::vector<std::size_t> rowsContainingMaximum;
        for (std::size_t row = 0; row < rowCount; ++row)
        {
            for (std::size_t column = 0; column < columnCount; ++column)
            {
                if (std::abs(matrix[row * columnCount + column]) == maximumByAbsoluteValue)
                {
                    rowsContainingMaximum.push_back(row);
                    break;
                }
            }
        }

        std::vector<int> firstRow(columnCount);
        for (std::size_t column = 0; column < columnCount; ++column)
        {
            firstRow[column] = matrix[column];
        }

        // Вставляем с конца, чтобы индексы ранее найденных строк не смещались.
        for (auto it = rowsContainingMaximum.rbegin(); it != rowsContainingMaximum.rend(); ++it)
        {
            matrix.insertRowAfter(*it, firstRow);
        }
    }
}
