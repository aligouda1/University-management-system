#ifndef Instructor_H
#define Instructor_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Announcement.h"
using namespace std;

enum Role { STUDENT = 1, ADMIN = 2, INSTRUCTOR = 3 };

class Instructor {
private:
    int    instructorId;
    string name;
    vector<int> courseIds;

    bool isValidId(int id, Role role) {
        int prefix = id / 1000;
        return prefix == role;
    }

public:
    Instructor(int id, string n);

    int    getID();
    string getName();
    void   assignCourses(int courseId);
    void   viewMyCourses();
    void   submitGrade(int studentId, int courseId, float mark);
    void   postAnnouncement(string title, string body, string date);
    void   showMenu();
    void   gradeAnalytics(vector<int>& studentIds, vector<float>& marks);
    void   gradeAppeal(Role role, int studentId, int courseId, string reason);
    bool   conflictChecker(vector<string>& existingSlots, string newSlot, string newCourseName);
};

#endif
