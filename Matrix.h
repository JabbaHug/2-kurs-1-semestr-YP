/**
 * @file Matrix.h
 * @brief Объявление класса двумерной целочисленной матрицы.
 */

#pragma once

#include "Generator.h"

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

namespace miit::algebra
{
    /**
     * @brief Класс двумерной целочисленной матрицы.
     *
     * Класс хранит матрицу целых чисел в одномерном объекте
     * std::vector<int>.
     *
     * Доступ к элементам выполняется через оператор [].
     * Класс поддерживает:
     * - создание матрицы;
     * - копирование и перемещение;
     * - заполнение значением;
     * - заполнение с помощью Generator;
     * - удаление столбцов;
     * - вставку строк;
     * - преобразование матрицы в строку;
     * - ввод и вывод через потоки.
     */
    class Matrix
    {
    private:

        /**
         * @brief Количество строк матрицы.
         *
         * Тип std::size_t используется для хранения
         * неотрицательного размера.
         */
        std::size_t rowCount;

        /**
         * @brief Количество столбцов матрицы.
         *
         * Тип std::size_t используется для хранения
         * неотрицательного размера.
         */
        std::size_t columnCount;

        /**
         * @brief Данные матрицы.
         *
         * std::vector<int> хранит все элементы матрицы
         * последовательно в памяти.
         */
        std::vector<int> data;

        /**
         * @brief Вычисляет плоский индекс элемента матрицы.
         *
         * @param row Номер строки типа std::size_t.
         * @param column Номер столбца типа std::size_t.
         *
         * @return Плоский индекс элемента в std::vector<int>.
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
         * @param rows Количество строк типа std::size_t.
         * @param columns Количество столбцов типа std::size_t.
         */
        Matrix(
            const std::size_t rows,
            const std::size_t columns
        );

        /**
         * @brief Создаёт матрицу и заполняет её значением.
         *
         * @param rows Количество строк типа std::size_t.
         * @param columns Количество столбцов типа std::size_t.
         * @param value Значение, которым заполняются все элементы.
         */
        Matrix(
            const std::size_t rows,
            const std::size_t columns,
            const int value
        );

        /**
         * @brief Конструктор копирования.
         *
         * @param other Исходная матрица.
         */
        Matrix(const Matrix& other) = default;

        /**
         * @brief Конструктор перемещения.
         *
         * @param other Матрица, из которой перемещаются данные.
         */
        Matrix(Matrix&& other) noexcept = default;

        /**
         * @brief Оператор копирующего присваивания.
         *
         * @param other Матрица, данные которой копируются.
         *
         * @return Ссылка на текущий объект Matrix.
         */
        Matrix& operator=(const Matrix& other) = default;

        /**
         * @brief Оператор перемещающего присваивания.
         *
         * @param other Матрица, данные которой перемещаются.
         *
         * @return Ссылка на текущий объект Matrix.
         */
        Matrix& operator=(Matrix&& other) noexcept = default;

        /**
         * @brief Деструктор матрицы.
         */
        ~Matrix() = default;

        /**
         * @brief Возвращает количество строк.
         *
         * @return Количество строк типа std::size_t.
         */
        std::size_t rows() const noexcept;

        /**
         * @brief Возвращает количество столбцов.
         *
         * @return Количество столбцов типа std::size_t.
         */
        std::size_t columns() const noexcept;

        /**
         * @brief Проверяет, является ли матрица пустой.
         *
         * @return true, если матрица не содержит элементов;
         * false в противном случае.
         */
        bool empty() const noexcept;

        /**
         * @brief Возвращает элемент матрицы по плоскому индексу.
         *
         * @param index Индекс элемента типа std::size_t.
         *
         * @return Ссылка на элемент типа int.
         *
         * @throw std::out_of_range Если индекс выходит
         * за границы матрицы.
         */
        int& operator[](const std::size_t index);

        /**
         * @brief Возвращает элемент константной матрицы.
         *
         * @param index Индекс элемента типа std::size_t.
         *
         * @return Константная ссылка на элемент типа int.
         *
         * @throw std::out_of_range Если индекс выходит
         * за границы матрицы.
         */
        const int& operator[](const std::size_t index) const;

        /**
         * @brief Заполняет матрицу значениями генератора.
         *
         * Для каждого элемента вызывается метод
         * Generator::generate().
         *
         * @param generator Генератор значений.
         */
        void fill(Generator& generator);

        /**
         * @brief Заполняет матрицу постоянным значением.
         *
         * @param value Значение для заполнения.
         */
        void fill(const int value);

        /**
         * @brief Удаляет один столбец матрицы.
         *
         * @param column Номер удаляемого столбца типа std::size_t.
         *
         * @throw std::out_of_range Если номер столбца
         * выходит за границы матрицы.
         */
        void removeColumn(const std::size_t column);

        /**
         * @brief Вставляет строку после указанной строки.
         *
         * @param row Номер строки, после которой выполняется вставка.
         * @param values Элементы вставляемой строки (размер должен
         * совпадать с количеством столбцов).
         *
         * @throw std::out_of_range Если номер строки выходит за границы.
         * @throw std::invalid_argument Если размер values не совпадает
         * с количеством столбцов.
         */
        void insertRowAfter(const std::size_t row, const std::vector<int>& values);

        /**
         * @brief Преобразует матрицу в строку.
         *
         * std::string содержит элементы матрицы,
         * разделённые пробелами и переносами строк.
         *
         * @return Строковое представление матрицы.
         */
        std::string toString() const;

        /**
         * @brief Выводит матрицу в поток.
         *
         * @param output Объект std::ostream,
         * в который выполняется вывод.
         * @param matrix Матрица для вывода.
         *
         * @return Ссылка на std::ostream.
         */
        friend std::ostream& operator<<(
            std::ostream& output,
            const Matrix& matrix
        );

        /**
         * @brief Считывает элементы матрицы из потока.
         *
         * @param input Объект std::istream,
         * из которого выполняется ввод.
         * @param matrix Матрица, которую необходимо заполнить.
         *
         * @return Ссылка на std::istream.
         */
        friend std::istream& operator>>(
            std::istream& input,
            Matrix& matrix
        );
    };
}
