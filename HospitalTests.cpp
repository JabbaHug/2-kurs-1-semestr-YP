#include "CppUnitTest.h"

#include "Doctor.h"
#include "Hospital.h"
#include "Nurse.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
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
                std::vector<std::string>{"Смирнов А.А."}
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

            std::unique_ptr<MedicalWorker> doctor =
                std::make_unique<Doctor>(
                    "Иванов Иван",
                    "Терапия",
                    "Терапевт",
                    std::vector<std::string>{"Пациент"}
                );

            const std::string expectedDoctor =
                doctor->toString();

            hospital.addWorker(std::move(doctor));

            Assert::IsTrue(doctor == nullptr);

            auto nurse = std::make_unique<Nurse>(
                "Петрова Анна",
                "Терапия",
                "Дневная"
            );

            const std::string expectedNurse =
                nurse->toString();

            hospital.addWorker(std::move(nurse));

            const auto& workers = hospital.getWorkers();

            Assert::AreEqual<std::size_t>(2, workers.size());

            Assert::AreEqual(
                expectedDoctor,
                workers[0]->toString()
            );

            Assert::AreEqual(
                expectedNurse,
                workers[1]->toString()
            );

            Assert::AreEqual(
                std::string(
                    "ГКБ №1, работников: 2, палат: 0"
                ),
                hospital.toString()
            );
        }

        TEST_METHOD(Hospital_RejectsNullWorker)
        {
            Hospital hospital("ГКБ №1");

            Assert::ExpectException<std::invalid_argument>(
                [&hospital]()
                {
                    hospital.addWorker(nullptr);
                }
            );

            Assert::IsTrue(hospital.getWorkers().empty());
        }
    };
}
