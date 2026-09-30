#include "Matrix.h"
#include <algorithm>
#include <ios>
#include <ostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace miit::algebra
{
    Matrix::Matrix() : rowCount(0), columnCount(0) {}

    Matrix::Matrix(const std::size_t rows, const std::size_t columns)
        : rowCount(rows), columnCount(columns), data(rows * columns) {}

    Matrix::Matrix(const std::size_t rows, const std::size_t columns, const int value)
        : rowCount(rows), columnCount(columns), data(rows * columns, value) {}

    std::size_t Matrix::offset(const std::size_t row, const std::size_t column) const
    {
        if (row >= rowCount || column >= columnCount)
            throw std::out_of_range("Matrix index is out of range");
        return row * columnCount + column;
    }

    std::size_t Matrix::rows() const noexcept { return rowCount; }
    std::size_t Matrix::columns() const noexcept { return columnCount; }
    bool Matrix::empty() const noexcept { return data.empty(); }

    int& Matrix::operator[](const std::size_t index)
    {
        if (index >= data.size()) throw std::out_of_range("Matrix index is out of range");
        return data[index];
    }

    const int& Matrix::operator[](const std::size_t index) const
    {
        if (index >= data.size()) throw std::out_of_range("Matrix index is out of range");
        return data[index];
    }

    void Matrix::fill(Generator& generator)
    {
        for (int& value : data) value = generator.generate();
    }

    void Matrix::fill(const int value) { std::fill(data.begin(), data.end(), value); }

    void Matrix::removeColumn(const std::size_t column)
    {
        if (column >= columnCount) throw std::out_of_range("Column index is out of range");
        std::vector<int> newData;
        newData.reserve(rowCount * (columnCount - 1));
        for (std::size_t row = 0; row < rowCount; ++row)
            for (std::size_t currentColumn = 0; currentColumn < columnCount; ++currentColumn)
                if (currentColumn != column) newData.push_back(data[row * columnCount + currentColumn]);
        --columnCount;
        data = std::move(newData);
    }

    void Matrix::insertRowAfter(const std::size_t row, const std::vector<int>& values)
    {
        if (row >= rowCount)
            throw std::out_of_range("Row index is out of range");
        if (values.size() != columnCount)
            throw std::invalid_argument("Row size does not match column count");

        const auto insertPosition = data.begin() + static_cast<std::ptrdiff_t>((row + 1) * columnCount);
        data.insert(insertPosition, values.begin(), values.end());
        ++rowCount;
    }

    std::string Matrix::toString() const
    {
        std::ostringstream output;
        for (std::size_t row = 0; row < rowCount; ++row)
        {
            for (std::size_t column = 0; column < columnCount; ++column)
            {
                if (column != 0) output << ' ';
                output << data[row * columnCount + column];
            }
            if (row + 1 < rowCount) output << '\n';
        }
        return output.str();
    }

    std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
    {
        output << matrix.toString();
        return output;
    }

    std::istream& operator>>(std::istream& input, Matrix& matrix)
    {
        for (int& value : matrix.data) input >> value;
        return input;
    }
}
