#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
public:
    int id;
    string name;
    string email;
    string password;
    string role;

    User();
    User(int id, string name, string email, string password, string role);

    void display();
};

string login();
void registerUser();
void resetPassword();

#endif
