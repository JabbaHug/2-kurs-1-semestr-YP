#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
    /**
     * @brief Базовый класс учебного задания над матрицей.
     *
     * Агрегирует матрицу и генератор и предоставляет общий интерфейс
     * для выполнения конкретного задания.
     * @tparam T Тип элементов матрицы.
     */
    template <typename T>
    class Exercise
    {
    protected:
        Matrix matrix;
        const Generator& generator;

    public:
        /**
         * @brief Создаёт задание и заполняет его матрицу.
         * @param rows Количество строк матрицы.
         * @param columns Количество столбцов матрицы.
         * @param generator Генератор значений для заполнения матрицы.
         */
        Exercise(const std::size_t rows, const std::size_t columns, const Generator& generator)
            : matrix(rows, columns),
              generator(generator)
        {
            matrix.fill(generator);
        }

        /**
         * @brief Виртуальный деструктор задания.
         */
        virtual ~Exercise() = default;

        /**
         * @brief Запрещённое копирование задания.
         */
        Exercise(const Exercise&) = delete;

        /**
         * @brief Запрещённое присваивание задания.
         * @return Ссылка на объект задания.
         */
        Exercise& operator=(const Exercise&) = delete;

        /**
         * @brief Выполняет конкретное задание над матрицей.
         */
        virtual void solve() = 0;

        /**
         * @brief Возвращает константную ссылку на матрицу.
         * @return Константная ссылка на матрицу задания.
         */
        const Matrix& getMatrix() const noexcept
        {
            return matrix;
        }

        /**
         * @brief Возвращает ссылку на матрицу для изменения.
         * @return Ссылка на матрицу задания.
         */
        Matrix& getMatrix() noexcept
        {
            return matrix;
        }
    };
}
