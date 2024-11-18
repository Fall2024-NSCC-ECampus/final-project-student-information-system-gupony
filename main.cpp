#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "Student.h"

using namespace std;

// Global weights for grade calculation
float weightMidterm1 = 0.25, weightMidterm2 = 0.25, weightFinal = 0.5;

// Function prototypes
void printMenu();
void addStudent(vector<Student>& students);
void printAllStudents(const vector<Student>& students);
void sortStudents(vector<Student>& students);
void printStudentsWithGrades(const vector<Student>& students);
void searchStudent(const vector<Student>& students);
void removeStudent(vector<Student>& students);
void saveStudentsToFile(const vector<Student>& students, const string& filename);
void loadStudentsFromFile(vector<Student>& students, const string& filename);
void setGradeWeights();

int main() {
    vector<Student> students;
    const string filename = "students.txt";
    int choice;

    do {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore();

        try {
            switch (choice) {
                case 1: addStudent(students); break;
                case 2: printAllStudents(students); break;
                case 3: sortStudents(students); break;
                case 4: printStudentsWithGrades(students); break;
                case 5: searchStudent(students); break;
                case 6: removeStudent(students); break;
                case 7: saveStudentsToFile(students, filename); break;
                case 8: loadStudentsFromFile(students, filename); break;
                case 9: setGradeWeights(); break;
                case 0: cout << "Exiting. Bye!\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 0);

    return 0;
}

void printMenu() {
    cout << "\nStudent Info System\n";
    cout << "1. Add a student\n";
    cout << "2. Show all students\n";
    cout << "3. Sort students by last name\n";
    cout << "4. Show students with letter grades\n";
    cout << "5. Search for a student\n";
    cout << "6. Remove a student\n";
    cout << "7. Save students to file\n";
    cout << "8. Load students from file\n";
    cout << "9. Set grade weights\n";
    cout << "0. Exit\n";
    cout << "Pick an option: ";
}

void addStudent(vector<Student>& students) {
    string firstName, lastName;
    int studentNumber;
    float midterm1, midterm2, finalExam;

    cout << "First name: ";
    getline(cin, firstName);
    cout << "Last name: ";
    getline(cin, lastName);
    cout << "Student number: ";
    cin >> studentNumber;
    cout << "Midterm 1 grade: ";
    cin >> midterm1;
    cout << "Midterm 2 grade: ";
    cin >> midterm2;
    cout << "Final exam grade: ";
    cin >> finalExam;

    students.emplace_back(firstName, lastName, studentNumber, midterm1, midterm2, finalExam);
    cout << "Student added!\n";
}

void printAllStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to show.\n";
        return;
    }

    cout << left << setw(15) << "First Name" << setw(15) << "Last Name"
         << setw(10) << "Student #" << setw(10) << "Midterm 1"
         << setw(10) << "Midterm 2" << setw(10) << "Final" << "\n";
    cout << string(70, '-') << "\n";

    for (const auto& student : students) {
        cout << left << setw(15) << student.getFirstName()
             << setw(15) << student.getLastName()
             << setw(10) << student.getStudentNumber()
             << setw(10) << student.getMidterm1()
             << setw(10) << student.getMidterm2()
             << setw(10) << student.getFinalExam() << "\n";
    }
}

void sortStudents(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to sort.\n";
        return;
    }

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.getLastName() == b.getLastName()) {
            return a.getFirstName() < b.getFirstName();
        }
        return a.getLastName() < b.getLastName();
    });

    cout << "Students sorted by last name.\n";
    printAllStudents(students);
}



void printStudentsWithGrades(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to show.\n";
        return;
    }

    for (const auto& student : students) {
        student.printStudent();
        cout << "Average Grade: " << student.calculateLetterGrade(weightMidterm1, weightMidterm2, weightFinal) << "\n";
        cout << "-----------------\n";
    }
}

void searchStudent(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to search.\n";
        return;
    }

    int studentNumber;
    cout << "Enter student number to search: ";
    cin >> studentNumber;

    for (const auto& student : students) {
        if (student.getStudentNumber() == studentNumber) {
            student.printStudent();
            return;
        }
    }

    cout << "Student not found.\n";
}

void removeStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to remove.\n";
        return;
    }

    int studentNumber;
    cout << "Enter student number to remove: ";
    cin >> studentNumber;

    auto it = remove_if(students.begin(), students.end(), [studentNumber](const Student& s) {
        return s.getStudentNumber() == studentNumber;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student removed.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void saveStudentsToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    outFile << students.size() << "\n";
    for (const auto& student : students) {
        student.saveToFile(outFile);
    }

    cout << "Students saved to file.\n";
}

void loadStudentsFromFile(vector<Student>& students, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file for reading.\n";
        return;
    }

    size_t count;
    inFile >> count;
    inFile.ignore();

    students.clear();
    for (size_t i = 0; i < count; ++i) {
        Student student;
        student.loadFromFile(inFile);
        students.push_back(student);
    }

    cout << "Students loaded from file.\n";
}

void setGradeWeights() {
    cout << "Enter weight for Midterm 1 (as a decimal or percentage): ";
    cin >> weightMidterm1;
    cout << "Enter weight for Midterm 2 (as a decimal or percentage): ";
    cin >> weightMidterm2;
    cout << "Enter weight for Final Exam (as a decimal or percentage): ";
    cin >> weightFinal;

    // Convert weights to fractions if entered as percentages
    if (weightMidterm1 > 1 || weightMidterm2 > 1 || weightFinal > 1) {
        cout << "Detected weights entered as percentages. Converting to fractions.\n";
        weightMidterm1 /= 100;
        weightMidterm2 /= 100;
        weightFinal /= 100;
    }

    // Validate that weights sum to 1
    float total = weightMidterm1 + weightMidterm2 + weightFinal;
    if (total != 1.0f) {
        cout << "Warning: Weights do not add up to 1. Adjusting automatically.\n";
        weightMidterm1 /= total;
        weightMidterm2 /= total;
        weightFinal /= total;
    }

    cout << "Grade weights updated.\n";
    cout << "New weights are: Midterm 1: " << weightMidterm1
         << ", Midterm 2: " << weightMidterm2
         << ", Final Exam: " << weightFinal << "\n";
}
