#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    std::string firstName;
    std::string lastName;
    int studentNumber;
    float midterm1;
    float midterm2;
    float finalExam;

public:
    // Constructors
    Student() = default;
    Student(std::string fn, std::string ln, int sn, float m1, float m2, float fe);

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    int getStudentNumber() const;
    float getMidterm1() const;
    float getMidterm2() const;
    float getFinalExam() const;

    // Setters
    void setFirstName(const std::string& fn);
    void setLastName(const std::string& ln);
    void setStudentNumber(int sn);
    void setMidterm1(float m1);
    void setMidterm2(float m2);
    void setFinalExam(float fe);

    // Utility
    float calculateAverage(float weight1, float weight2, float weight3) const;
    char calculateLetterGrade(float weight1, float weight2, float weight3) const;

    // Display
    void printStudent() const;

    // File I/O
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};

#endif
