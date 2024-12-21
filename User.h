#ifndef USER_H
#define USER_H
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class User {
private:
    string username;
    string email;
    string password;
    vector<string> friends;
    unordered_set<string> pendingRequests; 
    queue<string> notifications;

public:
    User() = default;
    User(const string& username, const string& email, const string& password);

    string getUsername() const;
    string getEmail() const;
    string getPassword() const;
    void addNotification(const string& notification);
    void showNotifications();

    void setEmail(const string& newEmail);
    void setPassword(const string& newPassword);

    void addFriend(const string& friendUsername);
    void removeFriend(const string& friendUsername);
    
    void sendFriendRequest(const string& user);
    void cancelFriendRequest(const string& user);
    void acceptFriendRequest(const string& user);
    void rejectFriendRequest(const string& user);

    const vector<string>& getFriends() const;
    unordered_set<string>& getPendingRequests();

    vector<string> getFriendRequests() const;
    bool isFriend(const string& username) const; 
    bool hasPendingRequest(const string& username) const;
};

#endif 
