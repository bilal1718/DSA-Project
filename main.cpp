#include <iostream>
#include "DataManager.h"
using namespace std;

void showMainMenu() {
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
}
void showFriendRequestMenu() {
    cout << "1. View Friends\n";
    cout << "2. Send Friend Request\n";
    cout << "3. View Friend Requests\n";
    cout << "4. Friend Suggestions\n";
    cout << "5. Back to Main Menu\n";
}

void showPostMenu() {
    cout << "1. Create Post\n";
    cout << "2. Edit Post\n";
    cout << "3. Delete Post\n";
    cout << "4. Like Post\n";
    cout << "5. Display Posts\n";
    cout << "6. Friends\n";
    cout << "7. View Notifications\n";
    cout << "8. Search Profiles\n";
    cout << "9. Logout\n";
}
void showSearchMenu() {
    cout << "1. Search Profiles\n";
    cout << "2. Back to Main Menu\n";
}

int main() {
    DataManager dataManager;
    
    if (!dataManager.loadUserData() || !dataManager.loadPostData() || !dataManager.loadFriendsList()) {
        cerr << "Error: Failed to load data!" << endl;
        return 1;
    }
    dataManager.loadUserData();
    dataManager.loadPostData();
    dataManager.loadFriendsList();

    string currentUser;
    bool loggedIn = false;

    while (true) {
        showMainMenu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) { 
            string username, email, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;
            if (dataManager.registerUser(username, email, password)) {
                dataManager.saveUserData();
                cout << "Registration successful!\n";
            } else {
                cout << "Error: Registration failed.\n";
            }
        } else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (dataManager.loginUser(username, password)) {
                loggedIn = true;
                currentUser = username;
                cout << "Login successful!\n";
            } else {
                cout << "Error: Login failed.\n";
            }
        } else if (choice == 3) { 
            dataManager.saveUserData();
            dataManager.savePostData();
            dataManager.saveFriendsList();
            cout << "Exiting program. Data saved.\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

        while (loggedIn) {
            showPostMenu();
            int postChoice;
            cout << "Enter your choice: ";
            cin >> postChoice;

            if (postChoice == 1) { 
                string content;
                cout << "Enter post content: ";
                cin.ignore();
                getline(cin, content);
                int postId = dataManager.createPost(currentUser, content);
                cout << "Post created with ID: " << postId << endl;
                            dataManager.savePostData();


            } else if (postChoice == 2) { 
                int postId;
                string newContent;
                cout << "Enter post ID to edit: ";
                cin >> postId;
                cout << "Enter new content: ";
                cin.ignore();
                getline(cin, newContent);
                if (dataManager.editPost(postId, newContent)) {
                    cout << "Post updated.\n";
                } else {
                    cout << "Error: Post not found.\n";
                }
                            dataManager.savePostData();


            } else if (postChoice == 3) { 
                int postId;
                cout << "Enter post ID to delete: ";
                cin >> postId;
                if (dataManager.deletePost(postId)) {
                    cout << "Post deleted.\n";
                } else {
                    cout << "Error: Post not found.\n";
                }
                            dataManager.savePostData();


            } else if (postChoice == 4) { 
                int postId;
                cout << "Enter post ID to like: ";
                cin >> postId;
                if (dataManager.likePost(postId)) {
                    dataManager.notifyPostLiked(postId, currentUser);
                    cout << "Post liked.\n";
                } else {
                    cout << "Error: Post not found.\n";
                }
                         dataManager.savePostData();

            } else if (postChoice == 5) {
                dataManager.displayPosts();

            } else if (postChoice == 6) { 
                while (true) {
                    showFriendRequestMenu();
                    int frChoice;
                    cout << "Enter your choice: ";
                    cin >> frChoice;

                    if (frChoice == 1) { 
                        dataManager.displayFriends(currentUser);

                    } else if (frChoice == 2) {
                        vector<string> nonFriends = dataManager.getNonFriends(currentUser);
                        if (nonFriends.empty()) {
                            cout << "No users available to send friend requests to.\n";
                        } else {
                            cout << "Available users to send friend requests:\n";
                            for (int i = 0; i < nonFriends.size(); ++i) {
                                cout << i + 1 << ". " << nonFriends[i] << endl;
                            }
                            int userIndex;
                            cout << "Enter the number of the user: ";
                            cin >> userIndex;
                            if (userIndex > 0 && userIndex <= nonFriends.size()) {
    string toUser = nonFriends[userIndex - 1];
    if (dataManager.sendFriendRequest(currentUser, toUser)) {
        cout << "Friend request sent to " << toUser << endl;
        dataManager.notifyNewFriendRequest(currentUser, toUser);
    } else {
        cout << "Error: Could not send friend request.\n";
    }
} else {
    cout << "Invalid selection.\n";
}
                        }
                    } else if (frChoice == 3) {
                        vector<string> friendRequests = dataManager.getFriendRequests(currentUser);
                        if (friendRequests.empty()) {
                            cout << "No friend requests available.\n";
                        } else {
                            cout << "Incoming friend requests:\n";
                            for (int i = 0; i < friendRequests.size(); ++i) {
                                cout << i + 1 << ". " << friendRequests[i] << endl;
                            }
                            int requestIndex;
                            cout << "Enter the number of the request to handle: ";
                            cin >> requestIndex;
                            if (requestIndex > 0 && requestIndex <= friendRequests.size()) {
                                cout << "1. Accept\n";
                                cout << "2. Reject\n";
                                int action;
                                cin >> action;
                                if (action == 1) {
                                    if (dataManager.acceptFriendRequest(friendRequests[requestIndex - 1], currentUser)) {
                                        cout << "Friend request accepted.\n";
                                            dataManager.saveFriendsList();

                                        dataManager.notifyAcceptedFriendRequest(currentUser,friendRequests[requestIndex - 1]);
                                    } else {
                                        cout << "Error: Could not accept friend request.\n";
                                    }
                                } else if (action == 2) {
                                    if (dataManager.rejectFriendRequest(friendRequests[requestIndex - 1], currentUser)) {
                                        cout << "Friend request rejected.\n";
                                    } else {
                                        cout << "Error: Could not reject friend request.\n";
                                    }
                                } else {
                                    cout << "Invalid action.\n";
                                }
                            } else {
                                cout << "Invalid selection.\n";
                            }
                        }

                    } 
                    else if (frChoice == 4) {
            vector<pair<string, int>> suggestions = dataManager.getFriendSuggestions(currentUser);
            if (suggestions.empty()) {
                cout << "No friend suggestions available.\n";
            } else {
                cout << "Friend Suggestions:\n";
                for (int i = 0; i < suggestions.size(); ++i) {
                    cout << i + 1 << ". " << suggestions[i].first
                         << " (Mutual Friends: " << suggestions[i].second << ")\n";
                }
                int suggestionIndex;
                cout << "Enter the number of the user to send a friend request: ";
                cin >> suggestionIndex;
                if (suggestionIndex > 0 && suggestionIndex <= suggestions.size()) {
                    string toUser = suggestions[suggestionIndex - 1].first;
                    if (dataManager.sendFriendRequest(currentUser, toUser)) {
                        cout << "Friend request sent to " << toUser << endl;
                        dataManager.notifyNewFriendRequest(currentUser, toUser);
                    } else {
                        cout << "Error: Could not send friend request.\n";
                    }
                } else {
                    cout << "Invalid selection.\n";
                }
            }
        }
                    
                    else if (frChoice == 5) {
                        break;
                    } else {
                        cout << "Invalid choice. Try again.\n";
                    }
                }

            }
            else if (postChoice == 7) {
dataManager.getUserData()[currentUser].showNotifications();
        } 

        else if (postChoice == 8) {
    while (true) {
        showSearchMenu();
        int searchChoice;
        cout << "Enter your choice: ";
        cin >> searchChoice;

        if (searchChoice == 1) {
            string searchQuery;
            cout << "Enter name or username to search: ";
            cin >> searchQuery;

            vector<string> searchResults = dataManager.searchProfiles(searchQuery);
            if (searchResults.empty()) {
                cout << "No profiles found matching the query.\n";
            } else {
                cout << "Search Results:\n";
                for (int i = 0; i < searchResults.size(); ++i) {
                    cout << i + 1 << ". " << searchResults[i] << endl;

                    vector<string> userPosts = dataManager.getUserPosts(searchResults[i]);
                    cout << "  Posts:\n";
                    for (const string& post : userPosts) {
                        cout << "    - " << post << endl;
                    }
                }

                int userIndex;
                cout << "Enter the number of the user to send a friend request or 0 to go back: ";
                cin >> userIndex;

                if (userIndex > 0 && userIndex <= searchResults.size()) {
                    string selectedUser = searchResults[userIndex - 1];
                    if (dataManager.sendFriendRequest(currentUser, selectedUser)) {
                        cout << "Friend request sent to " << selectedUser << ".\n";
                        dataManager.notifyNewFriendRequest(currentUser, selectedUser);
                    } else {
                        cout << "Error: Could not send friend request.\n";
                    }
                } else if (userIndex == 0) {
                    break;
                } else {
                    cout << "Invalid selection.\n";
                }
            }
        } else if (searchChoice == 2) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}
            
            else if (postChoice == 9) { 
                loggedIn = false;
                cout << "Logged out.\n";

            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    return 0;
}
