#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Course.h"
#include "Grade.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "Department.h"
#include "Announcement.h"
using namespace std;

// ── forward declarations ──────────────────────────────────────────────────────
void studentMenu(int userId, string userName, vector<Course>& courses);
void instructorMenu(int userId, string userName);
void adminMenu();

// ── helpers ───────────────────────────────────────────────────────────────────
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// =============================================================================
// MAIN — login gate
// =============================================================================
int main() {
    vector<Course> courses = {
        Course(101, "Data Structures",   "CS",  30, "Sun 10:00"),
        Course(102, "Calculus II",        "Math",25, "Mon 12:00"),
        Course(103, "Digital Logic",      "ENG", 20, "Tue 08:00"),
        Course(104, "OOP with C++",       "CS",  30, "Wed 10:00"),
        Course(105, "Linear Algebra",     "Math",25, "Thu 14:00"),
    };

    cout << "========================================\n";
    cout << "   University Management System\n";
    cout << "========================================\n\n";

    while (true) {
        cout << "1. Login\n2. Register\n3. Reset Password\n4. Exit\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string role = login();
            if (role == "student") {
                // For demo: create student object with id=1
                studentMenu(1, "Student", courses);
            } else if (role == "instructor") {
                instructorMenu(1, "Instructor");
            } else if (role == "admin") {
                adminMenu();
            } else {
                cout << "Login failed or account locked.\n";
            }
        } else if (choice == 2) {
            registerUser();
        } else if (choice == 3) {
            resetPassword();
        } else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}

// =============================================================================
// STUDENT MENU
// =============================================================================
void studentMenu(int userId, string userName, vector<Course>& courses) {
    Student s(userId, userName, "student@uni.edu");

    while (true) {
        cout << "\n========== Student Menu ==========\n";
        cout << "1. View All Courses\n";
        cout << "2. Enroll in a Course\n";
        cout << "3. Drop a Course\n";
        cout << "4. View My GPA\n";
        cout << "5. Export Transcript\n";
        cout << "6. Logout\n";
        cout << "Choice: ";
        int ch; cin >> ch; cin.ignore();

        if (ch == 1) {
            cout << "\n--- Available Courses ---\n";
            for (int i = 0; i < (int)courses.size(); i++)
                courses[i].display();

        } else if (ch == 2) {
            cout << "Enter Course ID to enroll: ";
            int cid; cin >> cid; cin.ignore();
            s.enroll(cid, courses);

        } else if (ch == 3) {
            cout << "Enter Course ID to drop: ";
            int cid; cin >> cid; cin.ignore();
            s.dropCourse(cid);

        } else if (ch == 4) {
            cout << "Your GPA: " << s.calculateGPA() << endl;

        } else if (ch == 5) {
            s.exportTranscript();

        } else if (ch == 6) {
            cout << "Logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

// =============================================================================
// INSTRUCTOR MENU
// =============================================================================
void instructorMenu(int userId, string userName) {
    Instructor ins(userId, userName);

    while (true) {
        cout << "\n========== Instructor Menu ==========\n";
        cout << "1. View My Courses\n";
        cout << "2. Assign Course\n";
        cout << "3. Submit Grade\n";
        cout << "4. Post Announcement\n";
        cout << "5. Grade Analytics\n";
        cout << "6. Grade Appeal\n";
        cout << "7. Logout\n";
        cout << "Choice: ";
        int ch; cin >> ch; cin.ignore();

        if (ch == 1) {
            ins.viewMyCourses();

        } else if (ch == 2) {
            cout << "Enter Course ID to assign: ";
            int cid; cin >> cid; cin.ignore();
            ins.assignCourses(cid);

        } else if (ch == 3) {
            cout << "Student ID: "; int sid; cin >> sid;
            cout << "Course ID: ";  int cid; cin >> cid;
            cout << "Mark: ";       float m;  cin >> m; cin.ignore();
            ins.submitGrade(sid, cid, m);

        } else if (ch == 4) {
            cout << "Title: "; string t; getline(cin, t);
            cout << "Body: ";  string b; getline(cin, b);
            cout << "Date: ";  string d; getline(cin, d);
            ins.postAnnouncement(t, b, d);

        } else if (ch == 5) {
            cout << "How many students? "; int n; cin >> n; cin.ignore();
            vector<int> ids; vector<float> marks;
            for (int i = 0; i < n; i++) {
                cout << "Student ID: "; int sid; cin >> sid; ids.push_back(sid);
                cout << "Mark: ";       float m;  cin >> m;  marks.push_back(m);
            }
            cin.ignore();
            ins.gradeAnalytics(ids, marks);

        } else if (ch == 6) {
            cout << "Student ID: "; int sid; cin >> sid;
            cout << "Course ID: ";  int cid; cin >> cid; cin.ignore();
            cout << "Reason: ";     string r; getline(cin, r);
            ins.gradeAppeal(STUDENT, sid, cid, r);

        } else if (ch == 7) {
            cout << "Logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

// =============================================================================
// ADMIN MENU
// =============================================================================
void adminMenu() {
    Admin admin("1", "Admin");

    while (true) {
        cout << "\n========== Admin Menu ==========\n";
        cout << "1. System Audit\n";
        cout << "2. Search\n";
        cout << "3. Send Warning Letters\n";
        cout << "4. Assign Instructor to Course\n";
        cout << "5. Add User\n";
        cout << "6. Remove User\n";
        cout << "7. Add Course\n";
        cout << "8. Manage Departments\n";
        cout << "9. Logout\n";
        cout << "Choice: ";
        int ch; cin >> ch; cin.ignore();

        if (ch == 1) {
            admin.generateSystemAudit();

        } else if (ch == 2) {
            cout << "Search keyword: "; string kw; getline(cin, kw);
            admin.searchEngine(kw);

        } else if (ch == 3) {
            admin.sendWarningLetters();

        } else if (ch == 4) {
            cout << "Instructor ID: "; string iid; getline(cin, iid);
            cout << "Course ID: ";     string cid; getline(cin, cid);
            admin.assignInstructor(iid, cid);

        } else if (ch == 5) {
            cout << "ID: ";    string id;   getline(cin, id);
            cout << "Name: ";  string nm;   getline(cin, nm);
            cout << "Role: ";  string rl;   getline(cin, rl);
            cout << "GPA: ";   string gpa;  getline(cin, gpa);
            admin.addUser(id, nm, rl, gpa);

        } else if (ch == 6) {
            cout << "User ID to remove: "; string uid; getline(cin, uid);
            admin.removeUser(uid);

        } else if (ch == 7) {
            cout << "Course ID: ";         string cid; getline(cin, cid);
            cout << "Course Name: ";       string cnm; getline(cin, cnm);
            cout << "Instructor ID: ";     string iid; getline(cin, iid);
            admin.addCourse(cid, cnm, iid);

        } else if (ch == 8) {
            cout << "Dept ID: ";   string did; getline(cin, did);
            cout << "Dept Name: "; string dnm; getline(cin, dnm);
            Department dept(did, dnm);
            cout << "1.Add Course  2.Remove Course  3.List Courses\nChoice: ";
            int dc; cin >> dc; cin.ignore();
            if (dc == 1) {
                cout << "Course ID: "; string c; getline(cin, c); dept.addCourse(c);
            } else if (dc == 2) {
                cout << "Course ID: "; string c; getline(cin, c); dept.removeCourse(c);
            } else if (dc == 3) {
                dept.listCourses();
            }

        } else if (ch == 9) {
            cout << "Logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}
