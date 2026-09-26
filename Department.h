#pragma once
#include <string>
#include <vector>

using namespace std;

class Department {
private:
    string deptID;
    string name;
    vector<string> courseIDs;

    void saveToFile(); // Keeps your files updated

public:
    Department(string d_id, string d_name);

    void addCourse(string courseID);
    void removeCourse(string courseID);
    void listCourses();
};