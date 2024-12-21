#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



vector<string> DataManager::searchProfiles(const string& query) {
    vector<string> searchResults;
    for (const auto& pair : userData) {
        const string& username = pair.first;
        const User& user = pair.second;
        if (username.find(query) != string::npos || user.getUsername().find(query) != string::npos) {
            searchResults.push_back(username);
        }
    }
    return searchResults;
}

vector<int> DataManager::getTrendingPosts(int topN) {
    vector<pair<int, int>> postLikes;

    for (const auto& pair : posts) {
        postLikes.push_back({pair.first, pair.second.getLikes()});
    }

    for (int i = 0; i < postLikes.size(); ++i) {
        for (int j = i + 1; j < postLikes.size(); ++j) {
            if (postLikes[j].second > postLikes[i].second) {
                pair<int, int> temp = postLikes[i];
                postLikes[i] = postLikes[j];
                postLikes[j] = temp;
            }
        }
    }

    vector<int> trendingPosts;
    for (int i = 0; i < topN && i < postLikes.size(); ++i) {
        trendingPosts.push_back(postLikes[i].first);
    }

    return trendingPosts;
}
vector<string> DataManager::getUserPosts(const string& username) {
    vector<string> userPosts;

    for (const auto& pair : posts) {
        const Post& post = pair.second;
        if (post.getUsername() == username) {
            userPosts.push_back(post.getContent());
        }
    }

    return userPosts;
}


bool DataManager::saveFriendsList() {
    ofstream outFile("C:/Users/CT/Desktop/dsa-project/friends_list.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open friends list file for saving!" << std::endl;
        return false;
    }

    for (const auto& pair : userData) {
        const string& username = pair.first;
        const User& user = pair.second;

        outFile << username << ":";
        const vector<string>& friends = user.getFriends();
        for (const string& friendName : friends) {
            outFile << friendName << ",";
        }
        outFile << "\n";
    }

    outFile.close();
    return true;
}

bool DataManager::loadFriendsList() {
    ifstream inFile("C:/Users/CT/Desktop/dsa-project/friends_list.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open friends list file for loading!" << std::endl;
        return false;
    }

    string line;
    while (std::getline(inFile, line)) {
        size_t colonPos = line.find(":");
        if (colonPos == string::npos) continue;

        string username = line.substr(0, colonPos);
        string friendsStr = line.substr(colonPos + 1);

        if (userData.find(username) == userData.end()) continue;

        User& user = userData[username];

        size_t pos = 0;
        while ((pos = friendsStr.find(",")) != string::npos) {
            string friendName = friendsStr.substr(0, pos);
            user.addFriend(friendName);
            friendsStr.erase(0, pos + 1);
        }
    }

    inFile.close();
    return true;
}
bool DataManager::sendFriendRequest(const string& fromUser, const string& toUser) {
    if (userData.find(toUser) != userData.end() && fromUser != toUser) {
        userData[toUser].sendFriendRequest(fromUser);
        return true;
    }
    return false;
}

bool DataManager::cancelFriendRequest(const string& fromUser, const string& toUser) {
    if (userData.find(toUser) != userData.end()) {
        userData[toUser].cancelFriendRequest(fromUser);
        return true;
    }
    return false;
}

bool DataManager::acceptFriendRequest(const string& fromUser, const string& toUser) {
    if (userData.find(toUser) != userData.end()) {
        userData[toUser].acceptFriendRequest(fromUser);
        userData[fromUser].addFriend(toUser);
        return true;
    }
    return false;
}

bool DataManager::rejectFriendRequest(const string& fromUser, const string& toUser) {
    if (userData.find(toUser) != userData.end()) {
        userData[toUser].rejectFriendRequest(fromUser);
        return true;
    }
    return false;
}
vector<string> DataManager::getFriendRequests(const string& username) {
    return userData[username].getFriendRequests();
}
vector<string> DataManager::getNonFriends(const string& username) {
    vector<string> nonFriends;
    for (const auto& pair : userData) {  
        const auto& user = pair.second; 
        if (user.getUsername() != username && 
            !user.isFriend(username) && 
            !user.hasPendingRequest(username)) {
            nonFriends.push_back(user.getUsername());
        }
    }
    return nonFriends;
}
void DataManager::displayFriends(const string& username) const {
    if (userData.find(username) != userData.end()) {
        const auto& friends = userData.at(username).getFriends();
        cout << "Friends of " << username << ":\n";
        for (const auto& friendName : friends) {
            cout << friendName << "\n";
        }
    } else {
        cout << "User not found.\n";
    }
}
bool DataManager::loadUserData() {
    ifstream file("C:\\Users\\CT\\Desktop\\dsa-project\\users.txt");
    if (!file.is_open()) {
        cout << "Failed to open users.txt or file does not exist.\n";
        return false; 
    }

    string username, email, password;
    while (file >> username >> email >> password) {
        userData[username] = User(username, email, password);
    }

    file.close();
    cout << "Loaded " << userData.size() << " users from file.\n";
    return true;
}

bool DataManager::saveUserData() {
    ofstream file("C:\\Users\\CT\\Desktop\\dsa-project\\users.txt", ios::trunc);
    if (!file.is_open()) {
        cout << "Failed to open users.txt for writing.\n";
        return false; 
    }
    for (auto it = userData.begin(); it != userData.end(); ++it) {
        file << it->second.getUsername() << " "
             << it->second.getEmail() << " "
             << it->second.getPassword() << "\n";
    }
    file.close();
    return true;
}

bool DataManager::registerUser(const string& username, const string& email, const string& password) {
    if (userData.find(username) != userData.end()) {
        cout << "Username already exists.\n";
        return false; 
    }

    userData[username] = User(username, email, password);
    cout << "Registration successful!\n";
    return true;
}

bool DataManager::loginUser(const string& username, const string& password) {
    auto it = userData.find(username);
    if (it != userData.end() && it->second.getPassword() == password) {
        cout << "Login successful! Welcome, " << username << ".\n";
        return true;
    }

    cout << "Invalid username or password.\n";
    return false;
}

int DataManager::createPost(const string& username, const string& content) {
    Post newPost(username, content);
    posts[postIdCounter] = newPost;
    return postIdCounter++;
}

bool DataManager::likePost(int postId) {
    if (posts.find(postId) != posts.end()) {
        posts[postId].addLike();
        
        return true;
    }
    return false;
}

bool DataManager::editPost(int postId, const string& newContent) {
    if (posts.find(postId) != posts.end()) {
        posts[postId].editContent(newContent);
        return true;
    }
    return false;
}

bool DataManager::deletePost(int postId) {
    if (posts.find(postId) != posts.end()) {
        posts[postId].deletePost();
        return true;
    }
    return false;
}

void DataManager::displayPosts() const {
    for (const auto& post : posts) {
        cout << "Post ID: " << post.first << "\n";
        cout << "User: " << post.second.getUsername() << "\n";
        cout << "Content: " << post.second.getContent() << "\n";
        cout << "Likes: " << post.second.getLikes() << "\n\n";
    }
}

unordered_map<int, Post>& DataManager::getPosts() {
    return posts;
}

unordered_map<string, User>& DataManager::getUsers() {
    return userData;
}

bool DataManager::loadPostData() {
    ifstream file("C:/Users/CT/Desktop/dsa-project/posts.txt");
    if (!file.is_open()) {
        cout << "Failed to open posts.txt or file does not exist.\n";
        return false;
    }
    posts.clear();
    file.clear();
    file.seekg(0); 

    int postId;
    string username;
    int likes;
    string content;

    while (file >> postId >> username >> likes) {
        file.ignore();
        getline(file, content); 
        if (!content.empty() && content[0] == '\"' && content.back() == '\"') {
            content = content.substr(1, content.size() - 2);
        }

        Post post(username, content);
        for (int i = 0; i < likes; ++i) {
            post.addLike();
        }
        posts[postId] = post;
    }

    file.close();
    cout << "Loaded " << posts.size() << " posts from file.\n";
    return true;
}
bool DataManager::savePostData() {
    ofstream file("C:/Users/CT/Desktop/dsa-project/posts.txt", ios::out);
    if (!file.is_open()) {
        cout << "Failed to open posts.txt for writing.\n";
        return false;
    }
    for (const auto& post : posts) {
        file << post.first << " "                              
             << post.second.getUsername() << " "              
             << post.second.getLikes() << " \""              
             << post.second.getContent() << "\"\n";        
    }

    file.close();
    return true;
}
void DataManager::notifyNewFriendRequest(const string& fromUser, const string& toUser) {
    if (userData.find(toUser) != userData.end()) {
        string notification = "You have a new friend request from " + fromUser + ".";
        userData[toUser].addNotification(notification);
    }
}

void DataManager::notifyAcceptedFriendRequest(const string& fromUser, const string& toUser) {
    if (userData.find(toUser) != userData.end()) {
        string notification = fromUser + " has accepted your friend request.";
        userData[toUser].addNotification(notification);
    }
}

void DataManager::notifyPostLiked(int postId, const string& liker) {
    if (posts.find(postId) != posts.end()) {
        string username = posts[postId].getUsername();
        if (userData.find(username) != userData.end()) {
            stringstream ss;
            ss << liker << " liked your post: \"" << posts[postId].getContent() << "\".";
            userData[username].addNotification(ss.str());
        }
    }
}

unordered_map<string, User>& DataManager::getUserData() {
    return userData;
}


vector<pair<string, int>> DataManager::getFriendSuggestions(const string& username) {
    vector<pair<string, int>> suggestions;

    if (userData.find(username) == userData.end()) return suggestions;

    const vector<string>& userFriends = userData[username].getFriends();
    unordered_set<string> userFriendSet(userFriends.begin(), userFriends.end());

    for (const auto& pair : userData) {
        const string& potentialFriend = pair.first;
        if (potentialFriend == username || userFriendSet.count(potentialFriend)) continue;

        const vector<string>& potentialFriendFriends = pair.second.getFriends();

        int mutualFriends = 0;
        for (const string& friendName : potentialFriendFriends) {
            if (userFriendSet.count(friendName)) {
                mutualFriends++;
            }
        }

        if (mutualFriends > 0) {
            suggestions.emplace_back(potentialFriend, mutualFriends);
        }
    }
    sort(suggestions.begin(), suggestions.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return b.second < a.second;
         });

    return suggestions;
}
