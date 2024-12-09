#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "PostManager.h"

using namespace std;

void showMenu() {
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

void showUserMenu() {
    cout << "\n--- User Menu ---\n";
    cout << "1. Create Post\n";
    cout << "2. View All Posts\n";
    cout << "3. Logout\n";
    cout << "Choose an option: ";
}

int main() {
    User::loadUsersFromFile();

    int choice;
    string username, email, password;
    PostManager postManager;
    User* loggedInUser = nullptr;

    while (true) {
        if (!loggedInUser) {
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
            } else if (choice == 2) {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                loggedInUser = User::loginUser(username, password);
                if (loggedInUser) {
                    cout << "Welcome, " << loggedInUser->username << "!" << endl;
                }
            } else if (choice == 3) {
                cout << "Exiting program...\n";
                break;
            } else {
                cout << "Invalid option. Please try again.\n";
            }
        } else {
            showUserMenu();
            cin >> choice;

            if (choice == 1) {
                string content;
                cout << "Enter post content: ";
                cin.ignore();
                getline(cin, content);
                postManager.createPost(content, loggedInUser->username);
            } else if (choice == 2) {
                vector<Post*> posts = postManager.getAllPosts();
                cout << "\n--- All Posts ---\n";
                for (const auto& post : posts) {
                    cout << "Post ID: " << post->postId << "\n";
                    cout << "Author: " << post->author << "\n";
                    cout << "Content: " << post->content << "\n";
                    cout << "Likes: " << post->likes << "\n\n";
                }
            } else if (choice == 3) {
                loggedInUser = nullptr;
                cout << "Logged out successfully.\n";
            } else {
                cout << "Invalid option. Please try again.\n";
            }
        }
    }

    return 0;
}
