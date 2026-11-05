#include "CppUnitTest.h"

#include "ConstantGenerator.h"
#include "FunctionGenerator.h"
#include "Generator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "SequenceGenerator.h"
#include "Task1.h"
#include "Task2.h"

#include <sstream>
#include <stdexcept>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace SolverTests
{
    TEST_CLASS(GeneratorTests)
    {
    public:
        TEST_METHOD(ConstantGenerator_Constructor)
        {
            ConstantGenerator generator(5);
            Assert::AreEqual(5, generator.generate());
        }

        TEST_METHOD(ConstantGenerator_Generate)
        {
            ConstantGenerator generator(10);
            Assert::AreEqual(10, generator.generate());
            Assert::AreEqual(10, generator.generate());
        }

        TEST_METHOD(FunctionGenerator_Generate)
        {
            int counter = 0;
            FunctionGenerator generator([&counter]() { return ++counter; });
            Assert::AreEqual(1, generator.generate());
            Assert::AreEqual(2, generator.generate());
        }

        TEST_METHOD(SequenceGenerator_Generate)
        {
            SequenceGenerator generator(std::vector<int>{4, 8, 15});
            Assert::AreEqual(4, generator.generate());
            Assert::AreEqual(8, generator.generate());
            Assert::AreEqual(15, generator.generate());
        }

        TEST_METHOD(SequenceGenerator_Throws)
        {
            SequenceGenerator generator(std::vector<int>{1});
            generator.generate();
            Assert::ExpectException<std::out_of_range>(
                [&generator]() { generator.generate(); }
            );
        }
    };

    TEST_CLASS(MatrixTests)
    {
    public:
        TEST_METHOD(Matrix_DefaultConstructor)
        {
            Matrix<int> matrix;
            Assert::AreEqual<std::size_t>(0, matrix.rows());
            Assert::AreEqual<std::size_t>(0, matrix.columns());
            Assert::IsTrue(matrix.empty());
        }

        TEST_METHOD(Matrix_SizeConstructor)
        {
            Matrix<int> matrix(2, 3);
            Assert::AreEqual<std::size_t>(2, matrix.rows());
            Assert::AreEqual<std::size_t>(3, matrix.columns());
        }

        TEST_METHOD(Matrix_ValueConstructor)
        {
            Matrix<int> matrix(2, 3, 7);
            for (std::size_t index = 0; index < 6; ++index)
                Assert::AreEqual(7, matrix[index]);
        }

        TEST_METHOD(Matrix_FillGenerator)
        {
            Matrix<int> matrix(2, 2);
            ConstantGenerator generator(8);
            matrix.fill(generator);
            for (std::size_t index = 0; index < 4; ++index)
                Assert::AreEqual(8, matrix[index]);
        }

        TEST_METHOD(Matrix_RemoveColumn)
        {
            Matrix<int> matrix(2, 3);
            matrix[0] = 1; matrix[1] = 2; matrix[2] = 3;
            matrix[3] = 4; matrix[4] = 5; matrix[5] = 6;
            matrix.removeColumn(1);
            Assert::AreEqual<std::size_t>(2, matrix.columns());
            Assert::AreEqual(1, matrix[0]);
            Assert::AreEqual(3, matrix[1]);
            Assert::AreEqual(4, matrix[2]);
            Assert::AreEqual(6, matrix[3]);
        }

        TEST_METHOD(Matrix_InsertRowAfter)
        {
            Matrix<int> matrix(2, 2);
            matrix[0] = 1; matrix[1] = 2;
            matrix[2] = 3; matrix[3] = 4;
            matrix.insertRowAfter(0, std::vector<int>{9, 8});
            Assert::AreEqual<std::size_t>(3, matrix.rows());
            Assert::AreEqual(9, matrix[2]);
            Assert::AreEqual(8, matrix[3]);
        }

        TEST_METHOD(Matrix_ToString)
        {
            Matrix<int> matrix(2, 2);
            matrix[0] = 1; matrix[1] = 2;
            matrix[2] = 3; matrix[3] = 4;
            Assert::AreEqual(std::string("1 2\n3 4"), matrix.toString());
        }
    };

    TEST_CLASS(TaskTests)
    {
    public:
        TEST_METHOD(Task1_Solve)
        {
            SequenceGenerator generator(
                std::vector<int>{5, 1, 4, 2, 9, 3}
            );
            Task1 task(2, 3, generator);
            task.solve();
            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(0, result[0]);
            Assert::AreEqual(1, result[1]);
            Assert::AreEqual(0, result[2]);
            Assert::AreEqual(2, result[3]);
            Assert::AreEqual(0, result[4]);
            Assert::AreEqual(3, result[5]);
        }

        TEST_METHOD(Task2_Solve)
        {
            SequenceGenerator generator(
                std::vector<int>{1, 2, 3, -5, 0, 1, 2, 4, -5}
            );
            Task2 task(3, 3, generator);
            task.solve();
            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual<std::size_t>(5, result.rows());
            Assert::AreEqual<std::size_t>(3, result.columns());
            Assert::AreEqual(1, result[0]);
            Assert::AreEqual(-5, result[3]);
            Assert::AreEqual(1, result[6]);
        }
    };
}
