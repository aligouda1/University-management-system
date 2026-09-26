#include "Instructor.h"
//phase 3 
// Instructor::Instructor(int id, string n, string email, string pass)
//     : User(id, n, email, pass, INSTRUCTOR) {}
Instructor::Instructor(int id, string n) { instructorId = id; name = n;}
string Instructor::getName() {	return name;}
 int Instructor::getID() { return instructorId; }
 void Instructor::assignCourses(int courseId) {//phase 3 move to ui class
     courseIds.push_back(courseId);
     cout << "Course: " << courseId << " assigned to " << name << endl;
 }
 void Instructor::viewMyCourses() {
     if (courseIds.empty()) {
         cout << "No courses assigned yet." << endl;
         return;
     }
     cout << "\t* Courses for " << name << "*" << endl;
     for (int i = 0; i < courseIds.size(); i++) {
         cout << "Course ID: " << courseIds[i] << endl;
     }
 }
 void Instructor::submitGrade(int studentId, int courseId, float mark) {//phase 3 replace  Grade g(studentId, courseId, mark); save g to grades.txt via FileManager (requires Abdelrahman's Grade class)
     cout << "Grade submitted:\nStudent: " << studentId<<"\nCourse: " << courseId<<"\nMark: " << mark << endl;
 }
 void Instructor::postAnnouncement(string title, string body, string date) {//phase 3 save to announcements.txt filemanager class
     Announcement a(title, body, date, instructorId);
     a.display();
 }
 void Instructor::gradeAnalytics(vector<int>& studentIds, vector<float>& marks) {
     if (marks.empty()) {
         cout << "No grades available." << endl;
         return;
     }
     else {
         float sum = 0;
         float highest = marks[0];
         float lowest = marks[0];
         int   passCount = 0;

         for (int i = 0; i < marks.size(); i++) {
             sum += marks[i];
             if (marks[i] > highest) highest = marks[i];
             if (marks[i] < lowest)  lowest = marks[i];
             if (marks[i] >= 50)     passCount++; 
         }

         float average = sum / marks.size();
         float passRate = (passCount * 100.0) / marks.size();

        
         cout << "\t* Student Grade list *" << endl;
         for (int i = 0; i < studentIds.size(); i++) {
             cout << "Student " << studentIds[i] << " : " << marks[i] << endl;
         }
         cout << "\t* Grade Analytics *" << endl;
         cout << "Average  : " << average << "\nHighest  : " << highest << "\nLowest   : " << lowest << "\nPass Rate: " << passRate << "%" << endl;
     }
 }

 bool Instructor::conflictChecker(vector<string>& existingSlots, string newSlot, string newCourseName) {
     if (existingSlots.empty()) {
         cout << "No existing courses, no conflict" << endl;
         return true;
     }
     for (int i = 0; i < existingSlots.size(); i++) {
         if (existingSlots[i] == newSlot) {
             cerr << "Time conflict! " << newCourseName<< " clashes at slot " << newSlot << endl;
             return false;
         }
     }
 
     cout << "No conflict. Safe to enroll in " << newCourseName << endl;
     return true;
 }
 void Instructor::gradeAppeal(Role role, int studentId, int courseId, string reason) {
     if (role == STUDENT && !isValidId(studentId, STUDENT)) {
         cerr << "Invalid student ID format." << endl;
         return;
     }
         switch (role) {

         case STUDENT: {
             ofstream file("appeal.txt", ios::app);
             if (!file.is_open()) {
                 cerr << "ERROR: Could not open appeals.txt" << endl;
                 return;
             }
             file << "Student " << studentId<< " appeals Course " << courseId << " - Reason: " << reason << endl;
             file.close();
             
             cout << "Appeal submitted successfully." << endl;
             break;
         }

         case INSTRUCTOR: {
             ifstream file("appeals.txt");
             if (!file.is_open()) {
                 cerr << "ERROR: No appeals found." << endl;
                 return;
             }
             string line;
             int appealNumber = 1;
             vector<string> appeals;
             while (getline(file, line)) {
                 cout << appealNumber << ". " << line << endl;
                 appeals.push_back(line);
                 appealNumber++;
             }
             file.close();

             if (appeals.empty()) {
                 cout << "No appeals to review." << endl;
                 return;
             }
             
             int choice;
             cout << "Enter appeal number to respond to: ";
             cin >> choice;

             if (choice < 1 || choice > appeals.size()) {
                 cerr << "ERROR: Invalid choice." << endl;
                 return;
             }

             int decision;
             cout << "1. Approve\n2. Reject\nChoice: ";
             cin >> decision;

             switch (decision) {
             case 1:
                 //phase 3 trigger gradeupdate abdo grade class
                 cout << "Appeal approved. Update the grade." << endl;
                 break;
             case 2:
                 cout << "Appeal rejected." << endl;
                 break;
             default:
                 cerr << "ERROR: Invalid decision." << endl;
             }
             break;
         }

         case ADMIN:
             cerr << "ERROR: Admin cannot use grade appeal." << endl;
             break;

         default:
             cerr << "ERROR: Unknown role." << endl;
         
     }
  }

 void Instructor::showMenu() {
     // UI::showInstructorMenu() handles this
     cout << "\t* Instructor Menu *" << endl << "1. View my courses\n" << "2. Submit a grade\n" << "3. Post announcement\n" << "4. Grade analytics\n" << "5. Grade appeals\n" << "6. Logout\n" << endl;
 }