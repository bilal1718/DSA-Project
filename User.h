#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "PostManager.h"

using namespace std;

class User {
public:
    static PostManager postManager;  
    // PostManager User::postManager;
    string username;
    string email;
    string password;

    queue<string> friendRequests;
    vector<string> friends;
    queue<string> notifications;

    User(string username, string email, string password);

    static bool registerUser(const string& username, const string& email, const string& password);
    static User* loginUser(const string& username, const string& password);

    static void saveUsersToFile();
    static void loadUsersFromFile();

    void addFriend(const string& friendUsername);
    void addFriendRequest(const string& sender);

    void addNotification(const string& message);
    void viewNotifications();

    static User* getUserByUsername(const string& username);

private:
    static unordered_map<string, User*> users;

    static string serializeQueue(queue<string> q);
    static queue<string> deserializeQueue(const string& data);
};

#endif
