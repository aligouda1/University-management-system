#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

User::User() {
    id = 0;
    name = "";
    email = "";
    password = "";
    role = "";
}

User::User(int id, string name, string email, string password, string role) {
    this->id = id;
    this->name = name;
    this->email = email;
    this->password = password;
    this->role = role;
}

void User::display() {
    cout << "ID: " << id << " | Name: " << name << " | Email: " << email << " | Role: " << role << endl;
}

string login() {
    string email, password;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

        ifstream file("users.txt");
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string sid, sname, semail, spassword, srole;

            getline(ss, sid, ',');
            getline(ss, sname, ',');
            getline(ss, semail, ',');
            getline(ss, spassword, ',');
            getline(ss, srole, ',');

            if (semail == email && spassword == password) {
                file.close();
                cout << "Login successful! Welcome " << sname << endl;
                return srole;
            }
        }

        file.close();
        attempts++;
        cout << "Wrong email or password. Attempts left: " << (3 - attempts) << endl;
    }

    cout << "Account locked. Too many wrong attempts." << endl;
    return "";
}

void registerUser() {
    string name, email, password;
    bool hasDigit = false;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter email: ";
    cin >> email;

    if (email.find('@') == string::npos || email.find('.') == string::npos) {
        cout << "Invalid email. Must contain '@' and '.'" << endl;
        return;
    }

    cout << "Enter password (min 8 chars, must have a number): ";
    cin >> password;

    if (password.length() < 8) {
        cout << "Password too short. Must be at least 8 characters." << endl;
        return;
    }

    for (int i = 0; i < password.length(); i++) {
        if (password[i] >= '0' && password[i] <= '9') {
            hasDigit = true;
        }
    }

    if (!hasDigit) {
        cout << "Password must contain at least one digit." << endl;
        return;
    }

    int newId = 1;
    ifstream readFile("users.txt");
    string line;
    while (getline(readFile, line)) {
        newId++;
    }
    readFile.close();

    ofstream file("users.txt", ios::app);
    file << newId << "," << name << "," << email << "," << password << ",student" << endl;
    file.close();

    cout << "Registration successful! Your ID is " << newId << endl;
}

void resetPassword() {
    string email, newPassword;
    bool hasDigit = false;
    bool found = false;

    cout << "Enter your email: ";
    cin >> email;

    ifstream readFile("users.txt");
    string line;
    vector<string> allLines;

    while (getline(readFile, line)) {
        allLines.push_back(line);
    }
    readFile.close();

    for (int i = 0; i < allLines.size(); i++) {
        stringstream ss(allLines[i]);
        string sid, sname, semail, spassword, srole;

        getline(ss, sid, ',');
        getline(ss, sname, ',');
        getline(ss, semail, ',');
        getline(ss, spassword, ',');
        getline(ss, srole, ',');

        if (semail == email) {
            found = true;

            cout << "Enter new password (min 8 chars, must have a number): ";
            cin >> newPassword;

            if (newPassword.length() < 8) {
                cout << "Password too short." << endl;
                return;
            }

            for (int j = 0; j < newPassword.length(); j++) {
                if (newPassword[j] >= '0' && newPassword[j] <= '9') {
                    hasDigit = true;
                }
            }

            if (!hasDigit) {
                cout << "Password must contain at least one digit." << endl;
                return;
            }

            allLines[i] = sid + "," + sname + "," + semail + "," + newPassword + "," + srole;
            break;
        }
    }

    if (!found) {
        cout << "Email not found." << endl;
        return;
    }

    ofstream writeFile("users.txt");
    for (int i = 0; i < allLines.size(); i++) {
        writeFile << allLines[i] << endl;
    }
    writeFile.close();

    cout << "Password updated successfully." << endl;
}
