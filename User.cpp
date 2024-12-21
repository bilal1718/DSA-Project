#include "User.h"
#include <iostream>
using namespace std;

User::User(const string& username, const string& email, const string& password)
    : username(username), email(email), password(password) {}

string User::getUsername() const {
    return username;
}

void User::addNotification(const string& notification) {
    notifications.push(notification);
}
void User::showNotifications() {
    if (notifications.empty()) {
        cout << "No new notifications.\n";
        return;
    }
    cout << "Notifications for " << username << ":\n";
    while (!notifications.empty()) {
        cout << "- " << notifications.front() << endl;
        notifications.pop();
    }
}

string User::getEmail() const {
    return email;
}

string User::getPassword() const {
    return password;
}

void User::setEmail(const string& newEmail) {
    email = newEmail;
}

void User::setPassword(const string& newPassword) {
    password = newPassword;
}

void User::addFriend(const string& friendUsername) {
    friends.push_back(friendUsername);
}

void User::removeFriend(const string& friendUsername) {
    friends.erase(remove(friends.begin(), friends.end(), friendUsername), friends.end());
}

void User::sendFriendRequest(const string& user) {
    pendingRequests.insert(user);
}

void User::cancelFriendRequest(const string& user) {
    pendingRequests.erase(user);
}

void User::acceptFriendRequest(const string& user) {
    if (pendingRequests.find(user) != pendingRequests.end()) {
        friends.push_back(user);
        pendingRequests.erase(user);
    }
}

void User::rejectFriendRequest(const string& user) {
    pendingRequests.erase(user);
}

const vector<string>& User::getFriends() const {
    return friends;
}

unordered_set<string>& User::getPendingRequests() {
    return pendingRequests;
}

vector<string> User::getFriendRequests() const {
    return vector<string>(pendingRequests.begin(), pendingRequests.end());
}

bool User::isFriend(const string& username) const {
    return find(friends.begin(), friends.end(), username) != friends.end();
}

bool User::hasPendingRequest(const string& username) const {
    return pendingRequests.find(username) != pendingRequests.end(); 
}
