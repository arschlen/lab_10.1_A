#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, PM, FI };
string specialnistStr[] = { "КН", "ПМ", "ФІ" };

struct Student {
    string prizv;
    int kurs;
    Specialnist specialnist;
    int ocinka_fizyka;
    int ocinka_matematyka;
    int ocinka_informatyka;
};

// Очищення вхідного буфера
void ClearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CreateStudents(Student* students, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;

        // Прізвище
        cout << " Прізвище: ";
        ClearInputBuffer(); // Очищення буфера перед введенням тексту
        getline(cin, students[i].prizv);

        // Курс
        cout << " Курс (1-4): ";
        while (!(cin >> students[i].kurs) || students[i].kurs < 1 || students[i].kurs > 4) {
            cout << " Помилка! Введіть ціле число від 1 до 4: ";
            ClearInputBuffer();
        }

        // Спеціальність
        cout << " Спеціальність (0 - КН, 1 - ПМ, 2 - ФІ): ";
        while (!(cin >> specialnist) || specialnist < 0 || specialnist > 2) {
            cout << " Помилка! Введіть 0, 1 або 2: ";
            ClearInputBuffer();
        }
        students[i].specialnist = (Specialnist)specialnist;

        // Оцінка з фізики
        cout << " Оцінка з фізики (2-5): ";
        while (!(cin >> students[i].ocinka_fizyka) || students[i].ocinka_fizyka < 2 || students[i].ocinka_fizyka > 5) {
            cout << " Помилка! Введіть оцінку від 2 до 5: ";
            ClearInputBuffer();
        }

        // Оцінка з математики
        cout << " Оцінка з математики (2-5): ";
        while (!(cin >> students[i].ocinka_matematyka) || students[i].ocinka_matematyka < 2 || students[i].ocinka_matematyka > 5) {
            cout << " Помилка! Введіть оцінку від 2 до 5: ";
            ClearInputBuffer();
        }

        // Оцінка з інформатики
        cout << " Оцінка з інформатики (2-5): ";
        while (!(cin >> students[i].ocinka_informatyka) || students[i].ocinka_informatyka < 2 || students[i].ocinka_informatyka > 5) {
            cout << " Помилка! Введіть оцінку від 2 до 5: ";
            ClearInputBuffer();
        }

        cout << endl;
    }
}

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

void PrintStudents(const Student* students, const int N) {
    cout << "=============================================================================================================" << endl;
    cout << "| № | Прізвище        | Курс | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з інформатики |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "|" << setw(2) << i + 1
            << " |  " << setw(15) << left << students[i].prizv
            << "|   " << setw(3) << students[i].kurs
            << "|" << setw(15) << specialnistStr[students[i].specialnist]
            << "|   " << setw(14) << students[i].ocinka_fizyka
            << "|   " << setw(18) << students[i].ocinka_matematyka
            << "| " << setw(20) << students[i].ocinka_informatyka << " |" << endl;
    }
    cout << "=============================================================================================================" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    while (!(cin >> N) || N <= 0) {
        cout << " Помилка! Введіть додатнє ціле число: ";
        ClearInputBuffer();
    }

    Student* students = new Student[N];

    CreateStudents(students, N);
    PrintStudents(students, N);

    int lowAvgCount = CountStudentsWithLowAverage(students, N);
    cout << "Кількість студентів, середній бал яких менший 4: " << lowAvgCount << endl;

    string lowestSubject = FindSubjectWithLowestAverage(students, N);
    cout << "Предмет із найнижчим середнім балом: " << lowestSubject << endl;

    delete[] students;
    return 0;
}
