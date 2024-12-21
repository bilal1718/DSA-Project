#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include "User.h"
#include "Post.h"

class DataManager {
private:
    unordered_map<string, User> userData;
    unordered_map<int, Post> posts;
    int postIdCounter = 0;

public:
    bool loadUserData();
    unordered_map<string, User>& getUserData(); // Add this accessor declaration

    bool saveUserData();
    bool savePostData();
    bool loadPostData();

    // Friends list file handling
    bool saveFriendsList();
    bool loadFriendsList();

    bool registerUser(const string& username, const string& email, const string& password);
    bool loginUser(const string& username, const string& password);
    int createPost(const string& username, const string& content);
    bool likePost(int postId);
    bool editPost(int postId, const string& newContent);
    bool deletePost(int postId);
    void displayPosts() const;

    // Friend Request Functions
    bool sendFriendRequest(const string& fromUser, const string& toUser);
    bool cancelFriendRequest(const string& fromUser, const string& toUser);
    bool acceptFriendRequest(const string& fromUser, const string& toUser);
    bool rejectFriendRequest(const string& fromUser, const string& toUser);
    void displayFriends(const string& username) const;
    vector<string> getNonFriends(const string& username);
    vector<string> getFriendRequests(const string& username);
    void notifyNewFriendRequest(const string& fromUser, const string& toUser);
void notifyAcceptedFriendRequest(const string& fromUser, const string& toUser);
void notifyPostLiked(int postId, const string& liker);

    // Accessor functions
    unordered_map<int, Post>& getPosts();
    unordered_map<string, User>& getUsers();
};

#endif
