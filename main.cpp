#include <iostream>
#include <limits>
#include <string>
#include "ConstantGenerator.h"
#include "FunctionGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

enum class GenerationMode { Random = 1, Keyboard = 2, Constant = 3 };
enum class TaskMode { First = 1, Second = 2 };

bool readInt(const std::string& message, int& value)
{
    std::cout << message;

    if (std::cin >> value)
    {
        return true;
    }

    std::cout << "Ошибка ввода.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

template <typename Task>
void printAndSolve(Task& task, const std::string& title)
{
    std::cout << "\nИсходная матрица:\n" << task.getMatrix() << '\n';
    task.solve();
    std::cout << "\n" << title << task.getMatrix() << '\n';
}

template <typename Generator>
int runTask(const int rows, const int columns, Generator& generator, const TaskMode taskMode)
{
    if (taskMode == TaskMode::First)
    {
        Task1 task(rows, columns, generator);
        printAndSolve(task, "После задания 1:\n");
        return 0;
    }
    if (taskMode == TaskMode::Second)
    {
        Task2 task(rows, columns, generator);
        printAndSolve(task, "После задания 2:\n");
        return 0;
    }
    return 1;
}

int main()
{
    int rows{};
    int columns{};
    int modeValue{};
    int taskValue{};

    if (!readInt("Введите количество строк: ", rows) ||
        !readInt("Введите количество столбцов: ", columns) ||
        !readInt("Заполнение: 1 - случайное, 2 - клавиатура, 3 - константа: ", modeValue) ||
        !readInt("Задание: 1 или 2: ", taskValue))
    {
        return 1;
    }

    if (rows < 0 || columns < 0)
    {
        std::cout << "Размеры матрицы не могут быть отрицательными.\n";
        return 1;
    }

    const auto mode = static_cast<GenerationMode>(modeValue);
    const auto taskMode = static_cast<TaskMode>(taskValue);

    switch (mode)
    {
    case GenerationMode::Random:
    {
        RandomGenerator generator(-10, 10);
        return runTask(rows, columns, generator, taskMode);
    }
    case GenerationMode::Keyboard:
    {
        FunctionGenerator generator([] {
            int value{};
            readInt("Введите элемент: ", value);
            return value;
        });
        return runTask(rows, columns, generator, taskMode);
    }
    case GenerationMode::Constant:
    {
        int value{};
        if (!readInt("Введите постоянное значение: ", value)) return 1;
        ConstantGenerator generator(value);
        return runTask(rows, columns, generator, taskMode);
    }
    default:
        std::cout << "Неизвестный режим заполнения.\n";
        return 1;
    }
}
