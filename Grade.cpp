#include "Grade.h"
#include <iostream>
using namespace std;

Grade::Grade(int inputStudentId, int inputCourseId, float inputMark) {
    studentId = inputStudentId;
    courseId  = inputCourseId;
    mark      = inputMark;
}

float Grade::getMark() {
    return mark;
}

int Grade::getStudentId() {
    return studentId;
}

int Grade::getCourseId() {
    return courseId;
}

void Grade::setMark(float m) {
    mark = m;
}

string Grade::getLetterGrade() {
    if (mark >= 90) return "A";
    if (mark >= 80) return "B";
    if (mark >= 70) return "C";
    if (mark >= 60) return "D";
    else            return "F";
}

bool Grade::isPassing() {
    return mark >= 50;
}

void Grade::display() {
    cout << "Student ID : " << studentId << endl;
    cout << "Course ID  : " << courseId  << endl;
    cout << "Mark       : " << mark      << endl;
    cout << "Grade      : " << getLetterGrade() << endl;
    cout << "Passing    : " << (isPassing() ? "Yes" : "No") << endl;
}
