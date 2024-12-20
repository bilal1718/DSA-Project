#include "User.h"
#include "PostManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


PostManager User::postManager;

unordered_map<string, User*> User::users;
User::User(string username, string email, string password)
    : username(username), email(email), password(password) {}

bool User::registerUser(const string& username, const string& email, const string& password) {
    if (users.find(username) != users.end()) {
        cout << "Username already exists!" << endl;
        return false;
    }
    users[username] = new User(username, email, password);
    cout << "Registration successful!" << endl;
    return true;
}
User* User::loginUser(const string& username, const string& password) {
    if (users.find(username) != users.end() && users[username]->password == password) {
        cout << "Login successful!" << endl;
        return users[username];
    }
    cout << "Invalid username or password!" << endl;
    return nullptr;
}
void User::addFriend(const string& friendUsername) {
    friends.push_back(friendUsername);
    addNotification("You are now friends with " + friendUsername);
}
void User::addFriendRequest(const string& sender) {
    friendRequests.push(sender);
    addNotification("You received a friend request from " + sender);
}
void User::addNotification(const string& message) {
    notifications.push(message);
}
void User::viewNotifications() {
    cout << "\n--- Notifications ---\n";
    while (!notifications.empty()) {
        cout << notifications.front() << endl;
        notifications.pop();
    }
    if (notifications.empty()) {
        cout << "No more notifications.\n";
    }
}
User* User::getUserByUsername(const string& username) {
    if (users.find(username) != users.end()) {
        return users[username];
    }
    return nullptr;
}
string User::serializeQueue(queue<string> q) {
    stringstream ss;
    while (!q.empty()) {
        ss << q.front() << "|";
        q.pop();
    }
    return ss.str();
}
queue<string> User::deserializeQueue(const string& data) {
    queue<string> q;
    stringstream ss(data);
    string item;
    while (getline(ss, item, '|')) {
        if (!item.empty()) {
            q.push(item);
        }
    }
    return q;
}

void User::saveUsersToFile() {
    ofstream outFile("C:/Users/CT/Desktop/semester3/DSA/project/users.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening file for saving!" << endl;
        return;
    }

    for (const auto& pair : users) {
        User* user = pair.second;
        outFile << "Username= " << user->username << "\n";
        outFile << "Email= " << user->email << "\n";
        outFile << "Password= " << user->password << "\n";
        for (const string& friendName : user->friends) {
            outFile << friendName << ",";
        }
        outFile << "\n";

        outFile << serializeQueue(user->friendRequests) << "\n";
        outFile << serializeQueue(user->notifications) << "\n";
            User::postManager.savePostsForUser(user->username);


        // Fetch the posts for the current user
        std::vector<Post*> userPosts = User::postManager.getAllPosts(); // Assuming this returns all posts
        std::vector<Post*> filteredPosts;
        for (Post* post : userPosts) {
            if (post->author == user->username) {
                filteredPosts.push_back(post);
            }
        }

        outFile << User::postManager.serializePostsForUser(filteredPosts) << "\n";
    }

    outFile.close();
    cout << "Users saved to file successfully!" << endl;
}


void User::loadUsersFromFile() {
    ifstream inFile("C:/Users/CT/Desktop/semester3/DSA/project/users.txt");
    if (!inFile.is_open()) {
        cerr << "Error opening file for loading!" << endl;
        return;
    }

    string username, email, password, friendsLine, requestsLine, notificationsLine, postsLine;
    while (getline(inFile, username)) {
        username = username.substr(10); // Remove "Username= "
    getline(inFile, email);
    email = email.substr(7); // Remove "Email= "
    getline(inFile, password);
    password = password.substr(10); // Remove "Password= "
        getline(inFile, friendsLine);
        getline(inFile, requestsLine);
        getline(inFile, notificationsLine);
        getline(inFile, postsLine); // Read posts for user

        User* user = new User(username, email, password);
        stringstream ss(friendsLine);
        string friendName;
        while (getline(ss, friendName, ',')) {
            if (!friendName.empty()) {
                user->friends.push_back(friendName);
            }
        }

        user->friendRequests = deserializeQueue(requestsLine);
        user->notifications = deserializeQueue(notificationsLine);

        User::postManager.loadPostsForUser(user->username);



std::vector<Post*> posts = User::postManager.deserializePostsForUser(postsLine);
for (Post* post : posts) {
    User::postManager.createPost(post->content, post->author);
}
        users[username] = user;
    }

    inFile.close();
    cout << "Users loaded from file successfully!" << endl;
}

