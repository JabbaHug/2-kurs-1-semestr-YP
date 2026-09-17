#include <iostream>
#include <limits>
#include <functional>

#include "../Solver/FunctionGenerator.h"
#include "../Solver/RandomGenerator.h"
#include "../Solver/Task1.h"
#include "../Solver/Task2.h"

using miit::algebra::FunctionGenerator;
using miit::algebra::RandomGenerator;
using miit::algebra::Task1;
using miit::algebra::Task2;

/**
 * @brief Выполняет безопасное чтение целочисленного значения из стандартного потока ввода cin.
 * @param message Текстовое приглашение для пользователя, выводимое в консоль.
 * @return Корректно считанное целое число.
 */
int readInt(const std::string& message)
{
    int value{};

    while (true)
    {
        std::cout << message;

        if (std::cin >> value)
        {
            return value;
        }

        std::cout << "Ошибка ввода. Повторите.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main()
{
    setlocale(LC_ALL, ".UTF8");

    const int rows = readInt("Введите количество строк: ");
    const int columns = readInt("Введите количество столбцов: ");

    if (rows < 0 || columns < 0)
    {
        std::cout << "Размеры не могут быть отрицательными.\n";
        return 1;
    }

    const int mode = readInt("Заполнение: 1 - случайное, 2 - с клавиатуры: ");
    const int taskNumber = readInt("Задание: 1 или 2: ");

    if (mode == 1)
    {
        RandomGenerator generator(-10, 10);

        if (taskNumber == 1)
        {
            Task1 task(rows, columns, generator);
            std::cout << "\nИсходная матрица:\n" << task.getMatrix() << '\n';
            task.solve();
            std::cout << "\nПосле задания 1 (нечетные заменены нулями):\n" << task.getMatrix() << '\n';
        }
        else if (taskNumber == 2)
        {
            Task2 task(rows, columns, generator);
            std::cout << "\nИсходная матрица:\n" << task.getMatrix() << '\n';
            task.solve();
            std::cout << "\nПосле задания 2 (вставка первого столбца после столбцов с 0):\n" << task.getMatrix() << '\n';
        }
        else
        {
            std::cout << "Неизвестный номер задания.\n";
            return 1;
        }
    }
    else if (mode == 2)
    {
        FunctionGenerator generator([]()
        {
            return readInt("Введите элемент: ");
        });

        if (taskNumber == 1)
        {
            Task1 task(rows, columns, generator);
            std::cout << "\nИсходная матрица:\n" << task.getMatrix() << '\n';
            task.solve();
            std::cout << "\nПосле задания 1 (нечетные заменены нулями):\n" << task.getMatrix() << '\n';
        }
        else if (taskNumber == 2)
        {
            Task2 task(rows, columns, generator);
            std::cout << "\nИсходная матрица:\n" << task.getMatrix() << '\n';
            task.solve();
            std::cout << "\nПосле задания 2 (вставка первого столбца после столбцов с 0):\n" << task.getMatrix() << '\n';
        }
        else
        {
            std::cout << "Неизвестный номер задания.\n";
            return 1;
        }
    }
    else
    {
        std::cout << "Неизвестный режим заполнения.\n";
        return 1;
    }

    return 0;
}
