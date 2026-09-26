#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Admin::Admin(string u_id, string u_name) { adminId = u_id; name = u_name; }

void Admin::generateSystemAudit() {
    ifstream courses_file("courses.txt");
    string courses_line;
    if (courses_file.is_open()) {
        while (getline(courses_file, courses_line)) {
            if (!courses_line.empty() && courses_line.back() == '\r') courses_line.pop_back();
            cout << courses_line << endl;
        }
        courses_file.close();
    }
    else {
        cout << "Unable to open courses.txt" << endl;
    }

    ifstream users_file("users.txt");
    string users_line;
    if (users_file.is_open()) {
        while (getline(users_file, users_line)) {
            if (!users_line.empty() && users_line.back() == '\r') users_line.pop_back();
            cout << users_line << endl;
        }
        users_file.close();
    }
    else {
        cout << "Unable to open users.txt" << endl;
    }
}

void Admin::searchEngine(string keyword) {
    ifstream courses_file("courses.txt");
    string courses_line;
    if (courses_file.is_open()) {
        while (getline(courses_file, courses_line)) {
            if (!courses_line.empty() && courses_line.back() == '\r') courses_line.pop_back();
            if ((int)courses_line.find(keyword) != -1) {
                cout << courses_line << endl;
            }
        }
        courses_file.close();
    }
    else {
        cout << "Unable to open courses.txt" << endl;
    }
    ifstream users_file("users.txt");
    string users_line;
    if (users_file.is_open()) {
        while (getline(users_file, users_line)) {
            if (!users_line.empty() && users_line.back() == '\r') users_line.pop_back();
            if ((int)users_line.find(keyword) != -1) {
                cout << users_line << endl;
            }
        }
        users_file.close();
    }
    else
    {
        cout << "Unable to open users.txt" << endl;
    }
}

void Admin::sendWarningLetters() {
    vector<string> students_name_waring;
    vector<string> students_id;
    ifstream users_file("users.txt");
    string users_line;
    if (users_file.is_open()) {
        while (getline(users_file, users_line)) {
            if (!users_line.empty() && users_line.back() == '\r') users_line.pop_back();
            stringstream ss(users_line);
            string id, name, role, gpa_str;
            double gpa;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, role, ',');
            getline(ss, gpa_str);
            gpa = stod(gpa_str);
            if (role == "Student" && gpa < 2) {
                cout << "Warning: Student " << name << " (ID " << id << ") has GPA " << gpa << " - below minimum\n";
                ofstream warn_file("warnings.txt", ios::trunc);
                warn_file << "Warning: Student " << name << " (ID " << id << ") has GPA " << gpa << " - below minimum" << endl;
                warn_file.close();
                students_name_waring.push_back(name);
                students_id.push_back(id);
            }
        }
        users_file.close();
    }
}

void Admin::assignInstructor(string instructorId, string courseId) {
    bool instructor_found = false;
    bool course_found = false;

    ifstream users_file("users.txt");
    string users_line;
    if (users_file.is_open()) {
        while (getline(users_file, users_line)) {
            if (!users_line.empty() && users_line.back() == '\r') users_line.pop_back();
            stringstream ss(users_line);
            string id, name, role, gpa_str;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, role, ',');
            getline(ss, gpa_str);
            if (id == instructorId && role == "Instructor") {
                instructor_found = true;
                break;
            }
        }
        users_file.close();
    }

    vector<string> all_courses;
    ifstream courses_file("courses.txt");
    string courses_line;
    if (courses_file.is_open()) {
        while (getline(courses_file, courses_line)) {
            if (!courses_line.empty() && courses_line.back() == '\r') courses_line.pop_back();
            stringstream ss(courses_line);
            string c_id, c_name, c_instructor;
            getline(ss, c_id, ',');
            getline(ss, c_name, ',');
            getline(ss, c_instructor);
            if (c_id == courseId) {
                course_found = true;
                string updated_courses_line = c_id + "," + c_name + "," + instructorId;
                all_courses.push_back(updated_courses_line);
            }
            else {
                all_courses.push_back(courses_line);
            }
        }
        courses_file.close();
    }

    if (instructor_found && course_found) {
        ofstream out_courses("courses.txt");
        for (int i = 0; i < (int)all_courses.size(); i++) {
            out_courses << all_courses[i] << endl;
        }
        out_courses.close();
        cout << "Success! Instructor assigned to the course.\n";
    }
    else if (!instructor_found) {
        cout << "Error: Instructor not found.\n";
    }
    else if (!course_found) {
        cout << "Error: Course not found.\n";
    }
}

void Admin::addUser(string new_id, string new_name, string new_role, string new_gpa) {
    ifstream check("users.txt");
    string line;
    while (getline(check, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');
        if (id == new_id) {
            cout << "Error: User ID already exists." << endl;
            check.close();
            return;
        }
    }
    check.close();

    ofstream users_file("users.txt", ios::app);
    if (users_file.is_open()) {
        users_file << new_id << "," << new_name << "," << new_role << "," << new_gpa << endl;
        users_file.close();
        cout << "Success! User added.\n";
    }
    else {
        cout << "Error: Unable to open users.txt\n";
    }
}
void Admin::removeUser(string target_id) {
    ifstream in("users.txt");
    vector<string> temporary_lines;// Store all lines except the one to remove work as a temporary storage for the lines we want to keep 
    string line;
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');// Extract the user ID from the line
        if (id == target_id) { found = true; continue; }// If the ID matches the target, we skip adding this line to the temporary storage
        temporary_lines.push_back(line);// If the ID does not match, we add the line to the temporary storage
    }
    in.close();
    if (!found) { cout << "User not found." << endl; return; }
    ofstream out("users.txt");
    for (int i = 0; i < (int)temporary_lines.size(); i++)
        out << temporary_lines[i] << endl;
    cout << "User removed." << endl;
}
void Admin::addCourse(string new_id, string new_name, string new_instructor) {
    ifstream check("courses.txt");
    string line;
    while (getline(check, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');
        if (id == new_id) {
            cout << "Error: Course ID already exists." << endl;
            check.close();
            return;
        }
    }
    check.close();
    ofstream courses_file("courses.txt", ios::app);// Open the file in ios::app = append mode to add the new course at the end bec as defult it will overwrite the file and we don't want that we want to keep the existing courses and add the new one at the end of the file  
    if (courses_file.is_open()) {
        courses_file << new_id << "," << new_name << "," << new_instructor << endl;
        courses_file.close();
        cout << "Success! Course added.\n";
    }
    else {
        cout << "Error: Unable to open courses.txt\n";
    }
}