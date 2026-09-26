#include "Announcement.h"

Announcement::Announcement(string t, string b, string d, int instructorId) {

    title = t;
    body = b;
    date = d;
    postedByInstructorId = instructorId;

}
string Announcement::getTitle() {return title;}
string Announcement::getBody() {return body;}
string Announcement::getDate() { return date;}
int Announcement::getPostedBy() { return postedByInstructorId;}
void Announcement::display() {
    cout << "\t* Announcement *" << endl;
    cout << "Title: " << title << "\nDate: " << date << "\nBody: " << body << "\nPosted by Instructor ID: " << postedByInstructorId << endl;
}