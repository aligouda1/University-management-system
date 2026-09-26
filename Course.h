#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course {
public:
    int id;
    string name;
    string department;
    int capacity;
    string instructorId;
    string timeSlot;
    vector<int> enrolledStudentIds;

    Course();
    Course(int id, string name, string department, int capacity, string timeSlot);

    bool isEnrolled(int studentId);
    bool isFull();
    void addStudent(int studentId);
    void removeStudent(int studentId);
    void display();

    // For Abdelrahman's Student class
    int getCourseID() { return id; }
    string getEnrollmentStatus() { return isFull() ? "FULL" : "OPEN"; }
};

#endif
