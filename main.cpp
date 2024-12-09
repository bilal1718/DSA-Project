#include <iostream>
#include <string>
#include "User.h"
using namespace std;

void showMenu() {
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    User::loadUsersFromFile();

    int choice;
    string username, email, password;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;

            User::registerUser(username, email, password);

            User::saveUsersToFile();
        } 
        else if (choice == 2) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            User* loggedInUser = User::loginUser(username, password);
            if (loggedInUser != nullptr) {
                cout << "Welcome, " << loggedInUser->username << "!" << endl;
            }
        } 
        else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } 
        else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
