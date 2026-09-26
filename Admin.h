#pragma once
#include <string>
using namespace std;

class Admin {
private:
    string adminId;
    string name;
public:
    Admin(string u_id, string u_name);

    void generateSystemAudit();
    void searchEngine(string keyword);
    void sendWarningLetters();
    void assignInstructor(string instructorId, string courseId);
    void addUser(string new_id, string new_name, string new_role, string new_gpa);
    void removeUser(string target_id);
    void addCourse(string new_id, string new_name, string new_instructor);
};
