#include "User.h"

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

void User::saveUsersToFile() {
    ofstream file("users.txt");
    for (const auto& pair : users) {
        file << pair.second->username << " "
             << pair.second->email << " "
             << pair.second->password << endl;
    }
    file.close();
}

void User::loadUsersFromFile() {
    ifstream file("users.txt");
    string username, email, password;

    while (file >> username >> email >> password) {
        users[username] = new User(username, email, password);
    }
    file.close();
}
