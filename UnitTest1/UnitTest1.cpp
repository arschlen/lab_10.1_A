#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

enum Specialnist { KN, PM, FI };

struct Student {
    string prizv;
    int kurs;
    Specialnist specialnist;
    int ocinka_fizyka;
    int ocinka_matematyka;
    int ocinka_informatyka;
};

int CountStudentsWithLowAverage(const Student* students, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        double avg = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_informatyka) / 3.0;
        if (avg < 4.0) {
            count++;
        }
    }
    return count;
}

string FindSubjectWithLowestAverage(const Student* students, const int N) {
    double sumPhysics = 0, sumMath = 0, sumInformatics = 0;

    for (int i = 0; i < N; i++) {
        sumPhysics += students[i].ocinka_fizyka;
        sumMath += students[i].ocinka_matematyka;
        sumInformatics += students[i].ocinka_informatyka;
    }

    double avgPhysics = sumPhysics / N;
    double avgMath = sumMath / N;
    double avgInformatics = sumInformatics / N;

    if (avgPhysics <= avgMath && avgPhysics <= avgInformatics)
        return "Фізика";
    else if (avgMath <= avgPhysics && avgMath <= avgInformatics)
        return "Математика";
    else
        return "Інформатика";
}

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestCountStudentsWithLowAverage)
        {
            // Тест для функції CountStudentsWithLowAverage
            Student students[] = {
                {"Іваненко", 1, KN, 3, 3, 3},
                {"Петренко", 2, PM, 4, 4, 4},
                {"Сидоренко", 3, FI, 2, 3, 2}
            };
            int count = CountStudentsWithLowAverage(students, 3);

            Assert::AreEqual(2, count); // Очікуємо 2 студенти з середнім балом < 4
        }

        TEST_METHOD(TestFindSubjectWithLowestAverage)
        {
            // Тест для функції FindSubjectWithLowestAverage
            Student students[] = {
                {"Іваненко", 1, KN, 3, 3, 5},
                {"Петренко", 2, PM, 4, 2, 4},
                {"Сидоренко", 3, FI, 5, 3, 3}
            };
            string subject = FindSubjectWithLowestAverage(students, 3);

            Assert::AreEqual(string("Математика"), subject); // Очікуємо "Математика"
        }
    };
}