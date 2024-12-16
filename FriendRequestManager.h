#ifndef FRIEND_REQUEST_MANAGER_H
#define FRIEND_REQUEST_MANAGER_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include "User.h"
using namespace std;

class FriendRequestManager {
public:
    void sendRequest(const string& sender, const string& receiver);
    void acceptRequest(const string& receiver, const string& sender);
    void rejectRequest(const string& receiver, const string& sender);
};

#endif