#include "Course.h"
#include <iostream>
using namespace std;

Course::Course() {
    id = 0;
    name = "";
    department = "";
    capacity = 0;
    instructorId = "";
    timeSlot = "";
}

Course::Course(int id, string name, string department, int capacity, string timeSlot) {
    this->id = id;
    this->name = name;
    this->department = department;
    this->capacity = capacity;
    this->timeSlot = timeSlot;
    this->instructorId = "";
}

bool Course::isEnrolled(int studentId) {
    for (int i = 0; i < enrolledStudentIds.size(); i++) {
        if (enrolledStudentIds[i] == studentId) {
            return true;
        }
    }
    return false;
}

bool Course::isFull() {
    return enrolledStudentIds.size() >= capacity;
}

void Course::addStudent(int studentId) {
    enrolledStudentIds.push_back(studentId);
}

void Course::removeStudent(int studentId) {
    for (int i = 0; i < enrolledStudentIds.size(); i++) {
        if (enrolledStudentIds[i] == studentId) {
            enrolledStudentIds.erase(enrolledStudentIds.begin() + i);
            return;
        }
    }
}

void Course::display() {
    cout << "ID: " << id << " | Name: " << name << " | Dept: " << department;
    cout << " | Capacity: " << enrolledStudentIds.size() << "/" << capacity;
    cout << " | Time: " << timeSlot << endl;
}
