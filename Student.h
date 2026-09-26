#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Grade.h"
#include "Course.h"
using namespace std;

class Student {
private:
    int            id;
    string         name;
    string         email;
    vector<Grade>  grades;
    string         nameOfFile;

public:
    Student(int ID, string Sname, string Smail);

    void addGrade(Grade g);
    float calculateGPA();
    void exportTranscript();
    void dropCourse(int courseID);
    bool enroll(int courseID, vector<Course>& Courses);
};

#endif
