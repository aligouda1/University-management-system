#include "Department.h"
#include <iostream>
#include <fstream>

using namespace std;

Department::Department(string d_id, string d_name) {
    deptID = d_id;
    name = d_name;

    // This forces it to save directly to a public folder on your C drive
    string filename = deptID + ".txt";
    ifstream inFile(filename);

    // If the file exists, load the courses
    if (inFile.is_open()) {
        string course;
        while (getline(inFile, course)) {
            if (course != "") {
                courseIDs.push_back(course);
            }
        }
        inFile.close();
    }
    else {
        // If it doesn't exist, create an empty file
        ofstream outFile(filename);
        outFile.close();
    }
}

// Rewrites the specific department's file
void Department::saveToFile() {
    // This forces it to save directly to a public folder on your C drive
    string filename = deptID + ".txt";
    ofstream outFile(filename);
    for (string course : courseIDs) {
        outFile << course << endl;
    }
    outFile.close();
}

void Department::addCourse(string courseID) {
    for (int i = 0; i < (int)courseIDs.size(); i++) {
        if (courseIDs[i] == courseID) {
            cout << "Course already exists." << endl;
            return;  // stop here, don't add again
        }
	}
    courseIDs.push_back(courseID);
    saveToFile();
    cout << "Added " << courseID << " to " << deptID << " department." << endl;
}

void Department::removeCourse(string courseID) {
    for (int i = 0; i < courseIDs.size(); i++) {
        if (courseIDs[i] == courseID) {
            courseIDs.erase(courseIDs.begin() + i);
            saveToFile();
            cout << "Removed " << courseID << " from " << deptID << " department." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

void Department::listCourses() {
    cout << "\n--- " << name << " (" << deptID << ") Courses ---" << endl;
    for (string course : courseIDs) {
        cout << "- " << course << endl;
    }
    cout << "---------------------------\n";
}