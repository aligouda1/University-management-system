#ifndef GRADE_H
#define GRADE_H

#include <string>
using namespace std;

class Grade {
private:
    int   studentId;
    int   courseId;
    float mark;

public:
    Grade(int inputStudentId, int inputCourseId, float inputMark);

    float getMark();
    int getStudentId();
    int getCourseId();
    void setMark(float m);
    string getLetterGrade();
    bool isPassing();
    void display();
};

#endif
