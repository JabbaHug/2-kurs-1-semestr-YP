#include "CppUnitTest.h"

#include "Solver/ConstantGenerator.h"
#include "Solver/FunctionGenerator.h"
#include "Solver/Generator.h"
#include "Solver/Matrix.h"
#include "Solver/RandomGenerator.h"
#include "Solver/SequenceGenerator.h"
#include "Solver/Task1.h"
#include "Solver/Task2.h"

#include <sstream>
#include <stdexcept>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace SolverTests
{
    /**
     * @brief Тесты генераторов.
     */
    TEST_CLASS(GeneratorTests)
    {
    public:

        /**
         * @brief Проверяет ConstantGenerator::ConstantGenerator().
         */
        TEST_METHOD(ConstantGenerator_Constructor)
        {
            ConstantGenerator generator(5);

            Assert::AreEqual(5, generator.generate());
        }

        /**
         * @brief Проверяет ConstantGenerator::generate().
         */
        TEST_METHOD(ConstantGenerator_Generate)
        {
            ConstantGenerator generator(10);

            Assert::AreEqual(10, generator.generate());
            Assert::AreEqual(10, generator.generate());
            Assert::AreEqual(10, generator.generate());
        }

        /**
         * @brief Проверяет FunctionGenerator::FunctionGenerator().
         */
        TEST_METHOD(FunctionGenerator_Constructor)
        {
            FunctionGenerator generator(
                []()
                {
                    return 25;
                }
            );

            Assert::AreEqual(25, generator.generate());
        }

        /**
         * @brief Проверяет FunctionGenerator::generate().
         */
        TEST_METHOD(FunctionGenerator_Generate)
        {
            int counter = 0;

            FunctionGenerator generator(
                [&counter]()
                {
                    return ++counter;
                }
            );

            Assert::AreEqual(1, generator.generate());
            Assert::AreEqual(2, generator.generate());
            Assert::AreEqual(3, generator.generate());
        }

        /**
         * @brief Проверяет конструктор SequenceGenerator.
         */
        TEST_METHOD(SequenceGenerator_Constructor)
        {
            SequenceGenerator generator(
                std::vector<int>{1, 2, 3}
            );

            Assert::AreEqual(1, generator.generate());
        }

        /**
         * @brief Проверяет последовательную генерацию.
         */
        TEST_METHOD(SequenceGenerator_Generate)
        {
            SequenceGenerator generator(
                std::vector<int>{4, 8, 15}
            );

            Assert::AreEqual(4, generator.generate());
            Assert::AreEqual(8, generator.generate());
            Assert::AreEqual(15, generator.generate());
        }

        /**
         * @brief Проверяет исключение после окончания последовательности.
         */
        TEST_METHOD(SequenceGenerator_Throws)
        {
            SequenceGenerator generator(
                std::vector<int>{1}
            );

            generator.generate();

            Assert::ExpectException<std::out_of_range>(
                [&generator]()
                {
                    generator.generate();
                }
            );
        }

        /**
         * @brief Проверяет удаление генератора через базовый класс.
         *
         * Тестирует виртуальный деструктор Generator.
         */
        TEST_METHOD(Generator_VirtualDestructor)
        {
            Generator* generator =
                new ConstantGenerator(7);

            Assert::AreEqual(
                7,
                generator->generate()
            );

            delete generator;
        }
    };


    /**
     * @brief Тесты класса Matrix.
     */
    TEST_CLASS(MatrixTests)
    {
    public:

        /**
         * @brief Проверяет конструктор по умолчанию.
         */
        TEST_METHOD(Matrix_DefaultConstructor)
        {
            Matrix matrix;

            Assert::AreEqual<std::size_t>(
                0,
                matrix.rows()
            );

            Assert::AreEqual<std::size_t>(
                0,
                matrix.columns()
            );

            Assert::IsTrue(matrix.empty());
        }

        /**
         * @brief Проверяет конструктор размера.
         */
        TEST_METHOD(Matrix_SizeConstructor)
        {
            Matrix matrix(2, 3);

            Assert::AreEqual<std::size_t>(
                2,
                matrix.rows()
            );

            Assert::AreEqual<std::size_t>(
                3,
                matrix.columns()
            );

            Assert::IsFalse(matrix.empty());
        }

        /**
         * @brief Проверяет конструктор с начальным значением.
         */
        TEST_METHOD(Matrix_ValueConstructor)
        {
            Matrix matrix(2, 3, 7);

            for (std::size_t index = 0; index < 6; ++index)
            {
                Assert::AreEqual(
                    7,
                    matrix[index]
                );
            }
        }

        /**
         * @brief Проверяет конструктор копирования.
         */
        TEST_METHOD(Matrix_CopyConstructor)
        {
            Matrix original(2, 2, 5);
            Matrix copy(original);

            Assert::AreEqual(
                original[0],
                copy[0]
            );

            Assert::AreEqual(
                original[3],
                copy[3]
            );
        }

        /**
         * @brief Проверяет конструктор перемещения.
         */
        TEST_METHOD(Matrix_MoveConstructor)
        {
            Matrix original(2, 2, 9);

            Matrix moved(
                std::move(original)
            );

            Assert::AreEqual(
                9,
                moved[0]
            );

            Assert::AreEqual(
                9,
                moved[3]
            );
        }

        /**
         * @brief Проверяет копирующее присваивание.
         */
        TEST_METHOD(Matrix_CopyAssignment)
        {
            Matrix first(2, 2, 3);
            Matrix second;

            second = first;

            Assert::AreEqual(
                3,
                second[0]
            );

            Assert::AreEqual(
                3,
                second[3]
            );
        }

        /**
         * @brief Проверяет перемещающее присваивание.
         */
        TEST_METHOD(Matrix_MoveAssignment)
        {
            Matrix first(2, 2, 6);
            Matrix second;

            second = std::move(first);

            Assert::AreEqual(
                6,
                second[0]
            );

            Assert::AreEqual(
                6,
                second[3]
            );
        }

        /**
         * @brief Проверяет rows().
         */
        TEST_METHOD(Matrix_Rows)
        {
            const Matrix matrix(4, 3);

            Assert::AreEqual<std::size_t>(
                4,
                matrix.rows()
            );
        }

        /**
         * @brief Проверяет columns().
         */
        TEST_METHOD(Matrix_Columns)
        {
            const Matrix matrix(4, 3);

            Assert::AreEqual<std::size_t>(
                3,
                matrix.columns()
            );
        }

        /**
         * @brief Проверяет empty().
         */
        TEST_METHOD(Matrix_Empty)
        {
            Matrix emptyMatrix;
            Matrix filledMatrix(1, 1);

            Assert::IsTrue(
                emptyMatrix.empty()
            );

            Assert::IsFalse(
                filledMatrix.empty()
            );
        }

        /**
         * @brief Проверяет неконстантный operator[].
         */
        TEST_METHOD(Matrix_NonConstOperator)
        {
            Matrix matrix(1, 2);

            matrix[0] = 10;
            matrix[1] = 20;

            Assert::AreEqual(
                10,
                matrix[0]
            );

            Assert::AreEqual(
                20,
                matrix[1]
            );
        }

        /**
         * @brief Проверяет константный operator[].
         */
        TEST_METHOD(Matrix_ConstOperator)
        {
            const Matrix matrix(1, 2, 15);

            const int first = matrix[0];
            const int second = matrix[1];

            Assert::AreEqual(15, first);
            Assert::AreEqual(15, second);
        }

        /**
         * @brief Проверяет operator[] при неверном индексе.
         */
        TEST_METHOD(Matrix_OperatorThrows)
        {
            Matrix matrix(1, 1);

            Assert::ExpectException<std::out_of_range>(
                [&matrix]()
                {
                    matrix[1];
                }
            );
        }

        /**
         * @brief Проверяет fill(Generator&).
         */
        TEST_METHOD(Matrix_FillGenerator)
        {
            Matrix matrix(2, 2);

            ConstantGenerator generator(8);

            matrix.fill(generator);

            for (std::size_t index = 0; index < 4; ++index)
            {
                Assert::AreEqual(
                    8,
                    matrix[index]
                );
            }
        }

        /**
         * @brief Проверяет fill(const int).
         */
        TEST_METHOD(Matrix_FillValue)
        {
            Matrix matrix(2, 3);

            matrix.fill(12);

            for (std::size_t index = 0; index < 6; ++index)
            {
                Assert::AreEqual(
                    12,
                    matrix[index]
                );
            }
        }

        /**
         * @brief Проверяет удаление столбца.
         */
        TEST_METHOD(Matrix_RemoveColumn)
        {
            Matrix matrix(2, 3);

            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;
            matrix[3] = 4;
            matrix[4] = 5;
            matrix[5] = 6;

            matrix.removeColumn(1);

            Assert::AreEqual<std::size_t>(
                2,
                matrix.columns()
            );

            Assert::AreEqual(1, matrix[0]);
            Assert::AreEqual(3, matrix[1]);
            Assert::AreEqual(4, matrix[2]);
            Assert::AreEqual(6, matrix[3]);
        }

        /**
         * @brief Проверяет ошибку при удалении несуществующего столбца.
         */
        TEST_METHOD(Matrix_RemoveColumnThrows)
        {
            Matrix matrix(2, 2);

            Assert::ExpectException<std::out_of_range>(
                [&matrix]()
                {
                    matrix.removeColumn(2);
                }
            );
        }

        /**
         * @brief Проверяет insertRowAfter.
         */
        TEST_METHOD(Matrix_InsertRowAfter)
        {
            Matrix matrix(2, 2);
            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;
            matrix[3] = 4;

            std::vector<int> newRow{9, 8};
            matrix.insertRowAfter(0, newRow);

            Assert::AreEqual<std::size_t>(3, matrix.rows());
            Assert::AreEqual(1, matrix[0]);
            Assert::AreEqual(2, matrix[1]);
            Assert::AreEqual(9, matrix[2]);
            Assert::AreEqual(8, matrix[3]);
            Assert::AreEqual(3, matrix[4]);
            Assert::AreEqual(4, matrix[5]);
        }

        /**
         * @brief Проверяет toString().
         */
        TEST_METHOD(Matrix_ToString)
        {
            Matrix matrix(2, 2);

            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;
            matrix[3] = 4;

            Assert::AreEqual(
                std::string("1 2\n3 4"),
                matrix.toString()
            );
        }

        /**
         * @brief Проверяет operator<<.
         */
        TEST_METHOD(Matrix_OutputOperator)
        {
            Matrix matrix(1, 2);

            matrix[0] = 5;
            matrix[1] = 10;

            std::stringstream output;

            output << matrix;

            Assert::AreEqual(
                std::string("5 10"),
                output.str()
            );
        }

        /**
         * @brief Проверяет operator>>.
         */
        TEST_METHOD(Matrix_InputOperator)
        {
            Matrix matrix(1, 3);

            std::stringstream input(
                "10 20 30"
            );

            input >> matrix;

            Assert::AreEqual(10, matrix[0]);
            Assert::AreEqual(20, matrix[1]);
            Assert::AreEqual(30, matrix[2]);
        }
    };


    /**
     * @brief Тесты заданий варианта 8.
     */
    TEST_CLASS(TaskTests)
    {
    public:

        /**
         * @brief Проверяет конструктор Task1.
         */
        TEST_METHOD(Task1_Constructor)
        {
            ConstantGenerator generator(4);

            Task1 task(2, 3, generator);

            Assert::AreEqual<std::size_t>(
                2,
                task.getMatrix().rows()
            );

            Assert::AreEqual<std::size_t>(
                3,
                task.getMatrix().columns()
            );
        }

        /**
         * @brief Проверяет решение первого задания.
         *
         * Матрица:
         *  5  1  4
         *  2  9  3
         * Максимумы столбцов: 5, 9, 4 → становятся 0.
         */
        TEST_METHOD(Task1_Solve)
        {
            SequenceGenerator generator(
                std::vector<int>
                {
                    5, 1, 4,
                    2, 9, 3
                }
            );

            Task1 task(2, 3, generator);

            task.solve();

            const Matrix& result =
                task.getMatrix();

            Assert::AreEqual(0, result[0]);
            Assert::AreEqual(1, result[1]);
            Assert::AreEqual(0, result[2]);
            Assert::AreEqual(2, result[3]);
            Assert::AreEqual(0, result[4]);
            Assert::AreEqual(3, result[5]);
        }

        /**
         * @brief Проверяет неконстантный getMatrix().
         */
        TEST_METHOD(Task1_GetMatrixNonConst)
        {
            ConstantGenerator generator(1);

            Task1 task(2, 2, generator);

            Matrix& matrix =
                task.getMatrix();

            matrix[0] = 50;

            Assert::AreEqual(
                50,
                task.getMatrix()[0]
            );
        }

        /**
         * @brief Проверяет константный getMatrix().
         */
        TEST_METHOD(Task1_GetMatrixConst)
        {
            ConstantGenerator generator(1);

            Task1 task(2, 2, generator);

            const Task1& constTask = task;

            const Matrix& matrix =
                constTask.getMatrix();

            Assert::AreEqual(
                1,
                matrix[0]
            );
        }

        /**
         * @brief Проверяет конструктор Task2.
         */
        TEST_METHOD(Task2_Constructor)
        {
            ConstantGenerator generator(2);

            Task2 task(3, 4, generator);

            Assert::AreEqual<std::size_t>(
                3,
                task.getMatrix().rows()
            );

            Assert::AreEqual<std::size_t>(
                4,
                task.getMatrix().columns()
            );
        }

        /**
         * @brief Проверяет решение второго задания.
         *
         * Матрица:
         *  1  2  3
         * -5  0  1
         *  2  4 -5
         * Максимум по модулю = 5. Строки 1 и 2 содержат его.
         * После них вставляется первая строка (1 2 3).
         * Результат:
         *  1  2  3
         * -5  0  1
         *  1  2  3
         *  2  4 -5
         *  1  2  3
         */
        TEST_METHOD(Task2_Solve)
        {
            SequenceGenerator generator(
                std::vector<int>
                {
                    1, 2, 3,
                    -5, 0, 1,
                    2, 4, -5
                }
            );

            Task2 task(3, 3, generator);

            task.solve();

            const Matrix& result =
                task.getMatrix();

            Assert::AreEqual<std::size_t>(5, result.rows());
            Assert::AreEqual<std::size_t>(3, result.columns());

            Assert::AreEqual(1, result[0]);
            Assert::AreEqual(2, result[1]);
            Assert::AreEqual(3, result[2]);
            Assert::AreEqual(-5, result[3]);
            Assert::AreEqual(0, result[4]);
            Assert::AreEqual(1, result[5]);
            Assert::AreEqual(1, result[6]);
            Assert::AreEqual(2, result[7]);
            Assert::AreEqual(3, result[8]);
            Assert::AreEqual(2, result[9]);
            Assert::AreEqual(4, result[10]);
            Assert::AreEqual(-5, result[11]);
            Assert::AreEqual(1, result[12]);
            Assert::AreEqual(2, result[13]);
            Assert::AreEqual(3, result[14]);
        }
    };
}
