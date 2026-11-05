#include <iostream>
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
 * Работники выводятся как коллекция базового класса MedicalWorker.
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

    const Patient patient1("Смирнов Алексей Андреевич", "Пневмония", 101);
    const Patient patient2("Кузнецова Мария Олеговна", "Грипп", 101);
    const Patient patient3("Орлов Дмитрий Сергеевич", "Аппендицит", 205);

    Ward ward101(101, 4);
    ward101.addPatient(patient1);
    ward101.addPatient(patient2);

    Ward ward205(205, 2);
    ward205.addPatient(patient3);

    hospital.addWard(ward101);
    hospital.addWard(ward205);

    // Медицинские работники — Doctor и Nurse.

    hospital.addWorker(
        Doctor(
            "Иванов Иван Иванович",
            "Терапевтическое",
            "Терапевт",
            std::vector<Patient>{patient1, patient2}
        )
    );

    hospital.addWorker(
        Nurse(
            "Петрова Анна Сергеевна",
            "Терапевтическое",
            "Дневная"
        )
    );

    hospital.addWorker(
        Doctor(
            "Сидоров Пётр Николаевич",
            "Хирургическое",
            "Хирург",
            std::vector<Patient>{patient3}
        )
    );

    hospital.addWorker(
        Nurse(
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

    for (const std::reference_wrapper<const MedicalWorker>& worker
         : hospital.getWorkers())
    {
        std::cout << worker.get().toString() << "\n\n";
    }

    return 0;
}
