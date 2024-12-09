#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class User {
public:
    string username;
    string email;
    string password;
    
    User(string username, string email, string password);

    static bool registerUser(const string& username, const string& email, const string& password);
    static User* loginUser(const string& username, const string& password);

    static void saveUsersToFile();
    static void loadUsersFromFile();

private:
    static unordered_map<string, User*> users;
};

#endif
