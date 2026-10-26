/**
 * @file Matrix.h
 * @brief Объявление шаблонного класса двумерной матрицы.
 */

#pragma once

#include "Generator.h"

#include <algorithm>
#include <cstddef>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс двумерной матрицы.
     *
     * Класс хранит матрицу элементов типа T в одномерном объекте
     * std::vector<T>.
     *
     * Доступ к элементам выполняется через оператор [].
     * Класс поддерживает:
     * - создание матрицы;
     * - копирование и перемещение;
     * - заполнение значением;
     * - заполнение с помощью Generator (для целочисленных типов);
     * - удаление столбцов;
     * - вставку строк;
     * - преобразование матрицы в строку;
     * - ввод и вывод через потоки.
     *
     * @tparam T Тип элементов матрицы.
     */
    template <typename T>
    class Matrix
    {
    private:

        /**
         * @brief Количество строк матрицы.
         */
        std::size_t rowCount;

        /**
         * @brief Количество столбцов матрицы.
         */
        std::size_t columnCount;

        /**
         * @brief Данные матрицы.
         *
         * std::vector<T> хранит все элементы матрицы
         * последовательно в памяти.
         */
        std::vector<T> data;

        /**
         * @brief Вычисляет плоский индекс элемента матрицы.
         *
         * @param row Номер строки.
         * @param column Номер столбца.
         *
         * @return Плоский индекс элемента в std::vector<T>.
         *
         * @throw std::out_of_range Если строка или столбец
         * выходят за границы матрицы.
         */
        std::size_t offset(
            const std::size_t row,
            const std::size_t column
        ) const;

    public:

        /**
         * @brief Создаёт пустую матрицу.
         */
        Matrix();

        /**
         * @brief Создаёт матрицу заданного размера.
         *
         * @param rows Количество строк.
         * @param columns Количество столбцов.
         */
        Matrix(
            const std::size_t rows,
            const std::size_t columns
        );

        /**
         * @brief Создаёт матрицу и заполняет её значением.
         *
         * @param rows Количество строк.
         * @param columns Количество столбцов.
         * @param value Значение, которым заполняются все элементы.
         */
        Matrix(
            const std::size_t rows,
            const std::size_t columns,
            const T& value
        );

        /**
         * @brief Конструктор копирования.
         */
        Matrix(const Matrix& other) = default;

        /**
         * @brief Конструктор перемещения.
         */
        Matrix(Matrix&& other) noexcept = default;

        /**
         * @brief Оператор копирующего присваивания.
         */
        Matrix& operator=(const Matrix& other) = default;

        /**
         * @brief Оператор перемещающего присваивания.
         */
        Matrix& operator=(Matrix&& other) noexcept = default;

        /**
         * @brief Деструктор матрицы.
         */
        ~Matrix() = default;

        /**
         * @brief Возвращает количество строк.
         */
        std::size_t rows() const noexcept;

        /**
         * @brief Возвращает количество столбцов.
         */
        std::size_t columns() const noexcept;

        /**
         * @brief Проверяет, является ли матрица пустой.
         */
        bool empty() const noexcept;

        /**
         * @brief Возвращает элемент матрицы по плоскому индексу.
         */
        T& operator[](const std::size_t index);

        /**
         * @brief Возвращает элемент константной матрицы.
         */
        const T& operator[](const std::size_t index) const;

        /**
         * @brief Заполняет матрицу значениями генератора.
         *
         * Для каждого элемента вызывается Generator::generate().
         * Значение приводится к типу T.
         *
         * @param generator Генератор значений.
         */
        void fill(const Generator& generator);

        /**
         * @brief Заполняет матрицу постоянным значением.
         *
         * @param value Значение для заполнения.
         */
        void fill(const T& value);

        /**
         * @brief Удаляет один столбец матрицы.
         *
         * @param column Номер удаляемого столбца.
         *
         * @throw std::out_of_range Если номер столбца
         * выходит за границы матрицы.
         */
        void removeColumn(const std::size_t column);

        /**
         * @brief Вставляет строку после указанной строки.
         *
         * @param row Номер строки, после которой выполняется вставка.
         * @param values Элементы вставляемой строки.
         *
         * @throw std::out_of_range Если номер строки выходит за границы.
         * @throw std::invalid_argument Если размер values не совпадает
         * с количеством столбцов.
         */
        void insertRowAfter(const std::size_t row, const std::vector<T>& values);

        /**
         * @brief Преобразует матрицу в строку.
         */
        std::string toString() const;
    };

    /**
     * @brief Выводит матрицу в поток.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix);

    /**
     * @brief Считывает элементы матрицы из потока.
     */
    template <typename T>
    std::istream& operator>>(std::istream& input, Matrix<T>& matrix);

    // --- Реализация шаблона ---

    template <typename T>
    Matrix<T>::Matrix() : rowCount(0), columnCount(0) {}

    template <typename T>
    Matrix<T>::Matrix(const std::size_t rows, const std::size_t columns)
        : rowCount(rows), columnCount(columns), data(rows * columns) {}

    template <typename T>
    Matrix<T>::Matrix(const std::size_t rows, const std::size_t columns, const T& value)
        : rowCount(rows), columnCount(columns), data(rows * columns, value) {}

    template <typename T>
    std::size_t Matrix<T>::offset(const std::size_t row, const std::size_t column) const
    {
        if (row >= rowCount || column >= columnCount)
            throw std::out_of_range("Matrix index is out of range");
        return row * columnCount + column;
    }

    template <typename T>
    std::size_t Matrix<T>::rows() const noexcept { return rowCount; }

    template <typename T>
    std::size_t Matrix<T>::columns() const noexcept { return columnCount; }

    template <typename T>
    bool Matrix<T>::empty() const noexcept { return data.empty(); }

    template <typename T>
    T& Matrix<T>::operator[](const std::size_t index)
    {
        if (index >= data.size()) throw std::out_of_range("Matrix index is out of range");
        return data[index];
    }

    template <typename T>
    const T& Matrix<T>::operator[](const std::size_t index) const
    {
        if (index >= data.size()) throw std::out_of_range("Matrix index is out of range");
        return data[index];
    }

    template <typename T>
    void Matrix<T>::fill(const Generator& generator)
    {
        for (T& value : data)
            value = static_cast<T>(generator.generate());
    }

    template <typename T>
    void Matrix<T>::fill(const T& value)
    {
        std::fill(data.begin(), data.end(), value);
    }

    template <typename T>
    void Matrix<T>::removeColumn(const std::size_t column)
    {
        if (column >= columnCount) throw std::out_of_range("Column index is out of range");
        std::vector<T> newData;
        newData.reserve(rowCount * (columnCount - 1));
        for (std::size_t row = 0; row < rowCount; ++row)
            for (std::size_t currentColumn = 0; currentColumn < columnCount; ++currentColumn)
                if (currentColumn != column)
                    newData.push_back(data[row * columnCount + currentColumn]);
        --columnCount;
        data = std::move(newData);
    }

    template <typename T>
    void Matrix<T>::insertRowAfter(const std::size_t row, const std::vector<T>& values)
    {
        if (row >= rowCount)
            throw std::out_of_range("Row index is out of range");
        if (values.size() != columnCount)
            throw std::invalid_argument("Row size does not match column count");

        const auto insertPosition = data.begin() + static_cast<std::ptrdiff_t>((row + 1) * columnCount);
        data.insert(insertPosition, values.begin(), values.end());
        ++rowCount;
    }

    template <typename T>
    std::string Matrix<T>::toString() const
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

    template <typename T>
    std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix)
    {
        output << matrix.toString();
        return output;
    }

    template <typename T>
    std::istream& operator>>(std::istream& input, Matrix<T>& matrix)
    {
        for (std::size_t index = 0; index < matrix.rows() * matrix.columns(); ++index)
            input >> matrix[index];
        return input;
    }
}
