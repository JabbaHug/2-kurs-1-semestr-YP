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
     * Класс хранит матрицу элементов типа T в двумерном объекте
     * std::vector<std::vector<T>>.
     *
     * Строки матрицы хранятся отдельными векторами, поэтому элементы
     * не лежат в памяти одним последовательным блоком.
     * Доступ к элементу выполняется через двойной оператор [][]:
     * matrix[row][column].
     * Класс поддерживает:
     * - создание матрицы;
     * - копирование и перемещение;
     * - создание матрицы с начальным значением;
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
         * @brief Двумерный вектор элементов матрицы.
         */
        std::vector<std::vector<T>> matrix;

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
         * @return Количество строк матрицы.
         */
        std::size_t rows() const noexcept;

        /**
         * @brief Возвращает количество столбцов.
         * @return Количество столбцов матрицы.
         */
        std::size_t columns() const noexcept;

        /**
         * @brief Проверяет, является ли матрица пустой.
         * @return true, если в матрице нет строк или нет столбцов, иначе false.
         */
        bool empty() const noexcept;

        /**
         * @brief Возвращает строку матрицы по её номеру.
         *
         * Элемент доступен через двойной оператор: matrix[row][column].
         * Выход за границы столбцов самим Matrix не проверяется.
         *
         * @param row Номер строки (нумерация с нуля).
         * @return Ссылка на строку матрицы.
         *
         * @throw std::out_of_range Если row выходит за границы матрицы.
         */
        std::vector<T>& operator[](const std::size_t row);

        /**
         * @brief Возвращает строку константной матрицы по её номеру.
         *
         * Элемент доступен через двойной оператор: matrix[row][column].
         * Выход за границы столбцов самим Matrix не проверяется.
         *
         * @param row Номер строки (нумерация с нуля).
         * @return Константная ссылка на строку матрицы.
         *
         * @throw std::out_of_range Если row выходит за границы матрицы.
         */
        const std::vector<T>& operator[](const std::size_t row) const;

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
         *
         * Элементы строки разделяются пробелом, строки матрицы -
         * символом перевода строки (после последней строки он не добавляется).
         *
         * @return Текстовое представление матрицы.
         */
        std::string toString() const;
    };

    /**
     * @brief Выводит матрицу в поток.
     * @param output Поток вывода.
     * @param matrix Выводимая матрица.
     * @return Ссылка на поток вывода.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix);

    /**
     * @brief Считывает элементы матрицы из потока.
     *
     * Элементы считываются построчно в уже заданные размеры матрицы.
     *
     * @param input Поток ввода.
     * @param matrix Матрица, в которую записываются элементы.
     * @return Ссылка на поток ввода.
     */
    template <typename T>
    std::istream& operator>>(std::istream& input, Matrix<T>& matrix);

    template <typename T>
    Matrix<T>::Matrix() : rowCount(0), columnCount(0) {}

    template <typename T>
    Matrix<T>::Matrix(const std::size_t rows, const std::size_t columns)
        : rowCount(rows), columnCount(columns), matrix(rows, std::vector<T>(columns)) {}

    template <typename T>
    Matrix<T>::Matrix(const std::size_t rows, const std::size_t columns, const T& value)
        : rowCount(rows), columnCount(columns), matrix(rows, std::vector<T>(columns, value)) {}

    template <typename T>
    std::size_t Matrix<T>::rows() const noexcept { return rowCount; }

    template <typename T>
    std::size_t Matrix<T>::columns() const noexcept { return columnCount; }

    template <typename T>
    bool Matrix<T>::empty() const noexcept { return rowCount == 0 || columnCount == 0; }

    template <typename T>
    std::vector<T>& Matrix<T>::operator[](const std::size_t row)
    {
        if (row >= rowCount) throw std::out_of_range("Matrix row index is out of range");
        return matrix[row];
    }

    template <typename T>
    const std::vector<T>& Matrix<T>::operator[](const std::size_t row) const
    {
        if (row >= rowCount) throw std::out_of_range("Matrix row index is out of range");
        return matrix[row];
    }

    template <typename T>
    void Matrix<T>::fill(const Generator& generator)
    {
        for (std::vector<T>& row : matrix)
            for (T& value : row)
                value = static_cast<T>(generator.generate());
    }

    template <typename T>
    void Matrix<T>::removeColumn(const std::size_t column)
    {
        if (column >= columnCount) throw std::out_of_range("Column index is out of range");
        for (std::vector<T>& row : matrix)
            row.erase(row.begin() + static_cast<std::ptrdiff_t>(column));
        --columnCount;
    }

    template <typename T>
    void Matrix<T>::insertRowAfter(const std::size_t row, const std::vector<T>& values)
    {
        if (row >= rowCount)
            throw std::out_of_range("Row index is out of range");
        if (values.size() != columnCount)
            throw std::invalid_argument("Row size does not match column count");

        const auto insertPosition = matrix.begin() + static_cast<std::ptrdiff_t>(row + 1);
        matrix.insert(insertPosition, values);
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
                output << matrix[row][column];
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
        for (std::size_t row = 0; row < matrix.rows(); ++row)
            for (std::size_t column = 0; column < matrix.columns(); ++column)
                input >> matrix[row][column];
        return input;
    }
}
