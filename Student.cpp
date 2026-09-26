#include "Student.h"
#include <iostream>
#include <fstream>
using namespace std;

Student::Student(int ID, string Sname, string Smail) {
    id    = ID;
    name  = Sname;
    email = Smail;
}

void Student::addGrade(Grade g) {
    grades.push_back(g);
}

float Student::calculateGPA() {
    if (grades.empty()) {
        return 0.0;
    }
    float total = 0;
    for (int i = 0; i < grades.size(); i++) {
        string letter = grades[i].getLetterGrade();
        if (letter == "A")      total += 4.0;
        else if (letter == "B") total += 3.0;
        else if (letter == "C") total += 2.0;
        else if (letter == "D") total += 1.0;
        else                    total += 0.0;
    }
    return total / grades.size();
}

void Student::exportTranscript() {

    string file = to_string(id) + ".txt";

    ofstream outFile(file);

    outFile << "Name: " << name << endl;
    outFile << "ID: "   << id   << endl;

    for (int i = 0; i < grades.size(); i++) {
        outFile << grades[i].getCourseId() << " " << grades[i].getMark() << endl;
    }

    outFile << "GPA: " << calculateGPA() << endl;

    outFile.close();

    cout << "Done! Saved to " << nameOfFile << endl;
}

void Student::dropCourse(int courseID) {

    if (grades.size() <= 2) {
        cout << "you cant drop any more " << endl;
        return;
    }

    for (int i = 0; i < grades.size(); i++) {
        if (grades[i].getCourseId() == courseID) {
            if (grades[i].getMark() > 0) {
                cout << "Course dropped with a 'W' grade." << endl;
            } else {
                grades.erase(grades.begin() + i);
                cout << "Course droped" << endl;
            }
            return;
        }
    }
}

bool Student::enroll(int courseID, vector<Course>& Courses) {

    int foundCourse = -1;
    for (int i = 0; i < Courses.size(); i++) {
        if (Courses[i].getCourseID() == courseID) {
            foundCourse = i;
        }
    }
    if (foundCourse == -1) {
        cout << "not exist" << endl;
        return false;
    }

    for (int i = 0; i < grades.size(); i++) {
        if (grades[i].getCourseId() == courseID) {
            cout << "You are in" << endl;
            return false;
        }
    }

    if (Courses[foundCourse].getEnrollmentStatus() == "FULL") {
        cout << "Course is full" << endl;
        return false;
    }

    Grade newGrade(this->id, courseID, 0.0);
    grades.push_back(newGrade);
    cout << "Enrolled successfully!" << endl;
    return true;
}
