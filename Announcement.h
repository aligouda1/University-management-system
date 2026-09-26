#ifndef Announcement_H
#define Announcement_H

#include<iostream>
#include<string>
using namespace std;

class Announcement {
private:

	string title;
	string body;
	string date;
	int postedByInstructorId;

public:
	Announcement(string t, string b, string d, int instructorId);

	string getTitle();
	string getBody();
	string getDate();
	int getPostedBy();
	void display(); //implement in .cpp
};
#endif

