#include "Student.h"
#include <stdexcept>

using namespace std;

// Constructor
Student::Student(string fn, string ln, int sn, float m1, float m2, float fe)
    : firstName(fn), lastName(ln), studentNumber(sn), midterm1(m1), midterm2(m2), finalExam(fe) {}

// Getters
string Student::getFirstName() const { return firstName; }
string Student::getLastName() const { return lastName; }
int Student::getStudentNumber() const { return studentNumber; }
float Student::getMidterm1() const { return midterm1; }
float Student::getMidterm2() const { return midterm2; }
float Student::getFinalExam() const { return finalExam; }

// Setters
void Student::setFirstName(const string& fn) { firstName = fn; }
void Student::setLastName(const string& ln) { lastName = ln; }
void Student::setStudentNumber(int sn) { studentNumber = sn; }
void Student::setMidterm1(float m1) { midterm1 = m1; }
void Student::setMidterm2(float m2) { midterm2 = m2; }
void Student::setFinalExam(float fe) { finalExam = fe; }

// Utility
float Student::calculateAverage(float weight1, float weight2, float weight3) const {
    return (midterm1 * weight1) + (midterm2 * weight2) + (finalExam * weight3);
}

char Student::calculateLetterGrade(float weight1, float weight2, float weight3) const {
    float avg = calculateAverage(weight1, weight2, weight3);
    if (avg > 90) return 'A';
    if (avg > 80) return 'B';
    if (avg > 70) return 'C';
    if (avg > 60) return 'D';
    return 'F';
}

// Display
void Student::printStudent() const {
    cout << "Name: " << firstName << " " << lastName << "\n";
    cout << "Student Number: " << studentNumber << "\n";
    cout << "Grades - Midterm 1: " << midterm1
         << ", Midterm 2: " << midterm2
         << ", Final Exam: " << finalExam << "\n";
}

// File I/O
void Student::saveToFile(ostream& out) const {
    out << firstName << "\n" << lastName << "\n"
        << studentNumber << "\n" << midterm1 << "\n"
        << midterm2 << "\n" << finalExam << "\n";
}

void Student::loadFromFile(istream& in) {
    getline(in, firstName);
    getline(in, lastName);
    in >> studentNumber >> midterm1 >> midterm2 >> finalExam;
    in.ignore();
}
