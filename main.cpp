#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Doctor.h"
#include "Hospital.h"
#include "Nurse.h"

/**
 * @brief Точка входа в демонстрационную программу.
 *
 * Создаёт больницу, отделения, палаты, пациентов
 * и медицинских работников.
 *
 * Работники хранятся как коллекция умных указателей
 * на базовый класс MedicalWorker. Вывод использует полиморфизм.
 *
 * @return 0 при успешном завершении.
 */
int main()
{
    Hospital hospital("Городская клиническая больница №1");

    // Отделения.

    hospital.addDepartment(Department("Терапевтическое"));
    hospital.addDepartment(Department("Хирургическое"));
    hospital.addDepartment(Department("Кардиологическое"));

    // Палаты и пациенты.

    Ward ward101(101, 4);
    ward101.addPatient(
        Patient("Смирнов Алексей Андреевич", "Пневмония", 101)
    );
    ward101.addPatient(
        Patient("Кузнецова Мария Олеговна", "Грипп", 101)
    );

    Ward ward205(205, 2);
    ward205.addPatient(
        Patient("Орлов Дмитрий Сергеевич", "Аппендицит", 205)
    );

    hospital.addWard(ward101);
    hospital.addWard(ward205);

    // Медицинские работники — Doctor и Nurse.

    hospital.addWorker(
        std::make_unique<Doctor>(
            "Иванов Иван Иванович",
            "Терапевтическое",
            "Терапевт",
            std::vector<std::string>{
                "Смирнов Алексей Андреевич",
                "Кузнецова Мария Олеговна"
            }
        )
    );

    hospital.addWorker(
        std::make_unique<Nurse>(
            "Петрова Анна Сергеевна",
            "Терапевтическое",
            "Дневная"
        )
    );

    hospital.addWorker(
        std::make_unique<Doctor>(
            "Сидоров Пётр Николаевич",
            "Хирургическое",
            "Хирург",
            std::vector<std::string>{
                "Орлов Дмитрий Сергеевич"
            }
        )
    );

    hospital.addWorker(
        std::make_unique<Nurse>(
            "Козлова Елена Викторовна",
            "Хирургическое",
            "Ночная"
        )
    );

    // Вывод информации.

    std::cout << hospital.toString() << "\n\n";

    std::cout << "Отделения:\n";

    for (const Department& item : hospital.getDepartments())
    {
        std::cout << item.toString() << '\n';
    }

    std::cout << "\nПалаты и пациенты:\n";

    for (const Ward& ward : hospital.getWards())
    {
        std::cout << ward.toString() << '\n';

        for (const Patient& patient : ward.getPatients())
        {
            std::cout << "  " << patient.toString() << '\n';
        }
    }

    std::cout << "\nМедицинские работники:\n";

    for (const std::unique_ptr<MedicalWorker>& worker
         : hospital.getWorkers())
    {
        std::cout << worker->toString() << "\n\n";
    }

    return 0;
}
