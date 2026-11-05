#include "CppUnitTest.h"

#include "Doctor.h"
#include "Hospital.h"
#include "Nurse.h"

#include <stdexcept>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HospitalTests
{
    TEST_CLASS(HospitalModelTests)
    {
    public:
        TEST_METHOD(Department_StoresData)
        {
            const Department department("Терапевтическое");

            Assert::AreEqual(
                std::string("Терапевтическое"),
                department.getName()
            );

            Assert::AreEqual(
                std::string("Терапевтическое"),
                department.toString()
            );
        }

        TEST_METHOD(Patient_StoresData)
        {
            const Patient patient("Иванов Иван", "Грипп", 101);

            Assert::AreEqual(
                std::string("Иванов Иван"),
                patient.getFullName()
            );

            Assert::AreEqual(
                std::string("Грипп"),
                patient.getDiagnosis()
            );

            Assert::AreEqual(
                101,
                patient.getWardNumber()
            );

            Assert::AreEqual(
                std::string(
                    "Иванов Иван, диагноз: Грипп, палата: 101"
                ),
                patient.toString()
            );
        }

        TEST_METHOD(Ward_StoresPatients)
        {
            Ward ward(101, 4);

            Assert::AreEqual(101, ward.getNumber());
            Assert::AreEqual(4, ward.getCapacity());
            Assert::IsTrue(ward.getPatients().empty());

            ward.addPatient(
                Patient("Иванов Иван", "Грипп", 101)
            );

            ward.addPatient(
                Patient("Петров Пётр", "Пневмония", 101)
            );

            Assert::AreEqual<std::size_t>(
                2,
                ward.getPatients().size()
            );

            Assert::AreEqual(
                std::string("Иванов Иван"),
                ward.getPatients()[0].getFullName()
            );

            Assert::AreEqual(
                std::string(
                    "Палата №101, вместимость: 4, пациентов: 2"
                ),
                ward.toString()
            );
        }

        TEST_METHOD(Doctor_StoresSpecializationAndPatients)
        {
            const Doctor doctor(
                "Иванов Иван",
                "Терапевтическое",
                "Терапевт",
                std::vector<Patient>{Patient("Смирнов А.А.", "ОРВИ", 101)}
            );

            Assert::AreEqual(
                std::string("Иванов Иван"),
                doctor.getFullName()
            );

            Assert::AreEqual(
                std::string("Терапевт"),
                doctor.getSpecialization()
            );

            Assert::IsTrue(
                doctor.observesPatient("Смирнов А.А.")
            );

            Assert::IsFalse(
                doctor.observesPatient("Неизвестный")
            );
        }

        TEST_METHOD(Nurse_StoresShift)
        {
            const Nurse nurse(
                "Петрова Анна",
                "Хирургическое",
                "Ночная"
            );

            Assert::AreEqual(
                std::string("Петрова Анна"),
                nurse.getFullName()
            );

            Assert::AreEqual(
                std::string("Ночная"),
                nurse.getShift()
            );

            Assert::AreEqual(
                std::string(
                    "Медсестра: Петрова Анна, "
                    "отделение: Хирургическое, смена: Ночная"
                ),
                nurse.toString()
            );
        }

        TEST_METHOD(Hospital_StoresCollections)
        {
            Hospital hospital("ГКБ №1");

            Assert::AreEqual(
                std::string("ГКБ №1"),
                hospital.getName()
            );

            Assert::IsTrue(hospital.getDepartments().empty());
            Assert::IsTrue(hospital.getWards().empty());
            Assert::IsTrue(hospital.getWorkers().empty());

            hospital.addDepartment(Department("Терапия"));

            Ward ward(101, 2);
            ward.addPatient(
                Patient("Иванов Иван", "Грипп", 101)
            );
            hospital.addWard(ward);

            Assert::AreEqual<std::size_t>(
                1,
                hospital.getDepartments().size()
            );

            Assert::AreEqual<std::size_t>(
                1,
                hospital.getWards().size()
            );

            Assert::AreEqual(
                std::string(
                    "ГКБ №1, работников: 0, палат: 1"
                ),
                hospital.toString()
            );
        }

        TEST_METHOD(Hospital_OwnsDifferentWorkerTypes)
        {
            Hospital hospital("ГКБ №1");

            const Doctor doctor(
                "Иванов Иван",
                "Терапия",
                "Терапевт",
                std::vector<Patient>{Patient("Пациент", "ОРВИ", 101)}
            );

            const std::string expectedDoctor = doctor.toString();
            hospital.addWorker(doctor);

            const Nurse nurse(
                "Петрова Анна",
                "Терапия",
                "Дневная"
            );

            const std::string expectedNurse = nurse.toString();
            hospital.addWorker(nurse);

            const auto& workers = hospital.getWorkers();

            Assert::AreEqual<std::size_t>(2, workers.size());

            Assert::AreEqual(
                expectedDoctor,
                workers[0].get().toString()
            );

            Assert::AreEqual(
                expectedNurse,
                workers[1].get().toString()
            );

            Assert::AreEqual(
                std::string(
                    "ГКБ №1, работников: 2, палат: 0"
                ),
                hospital.toString()
            );
        }

        TEST_METHOD(Person_IdIsUniqueAcrossPatientsAndWorkers)
        {
            const Patient first("Иванов Иван", "Грипп", 101);
            const Doctor doctor("Петров Пётр", "Терапия", "Терапевт", {first});
            const Nurse nurse("Сидорова Анна", "Терапия", "Дневная");
            const Patient second("Иванов Иван", "Грипп", 101);

            Assert::IsTrue(first.getId() != doctor.getId());
            Assert::IsTrue(first.getId() != nurse.getId());
            Assert::IsTrue(first.getId() != second.getId());
            Assert::IsTrue(doctor.getId() != nurse.getId());
        }

        TEST_METHOD(Doctor_StoresPatientsNotNames)
        {
            const Patient patient("Иванов Иван", "Грипп", 101);
            const Doctor doctor("Врач", "Терапия", "Терапевт", {patient});

            Assert::AreEqual<std::size_t>(1, doctor.getPatients().size());
            Assert::AreEqual(patient.getId(), doctor.getPatients()[0].getId());
            Assert::IsTrue(doctor.observesPatient(patient));
        }
    };
}
