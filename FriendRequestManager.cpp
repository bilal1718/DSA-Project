#include "FriendRequestManager.h"
#include "User.h"

void FriendRequestManager::sendRequest(const string& sender, const string& receiver) {
    User* senderUser = User::getUserByUsername(sender);
    User* receiverUser = User::getUserByUsername(receiver);

    if (senderUser && receiverUser) {
        receiverUser->addFriendRequest(sender);
        cout << "Friend request sent from " << sender << " to " << receiver << endl;
    } else {
        cout << "One or both users not found!" << endl;
    }
}

void FriendRequestManager::acceptRequest(const string& receiver, const string& sender) {
    User* receiverUser = User::getUserByUsername(receiver);
    User* senderUser = User::getUserByUsername(sender);

    if (receiverUser && senderUser) {
        if (!receiverUser->friendRequests.empty() && receiverUser->friendRequests.front() == sender) {
            receiverUser->friendRequests.pop();
            receiverUser->addFriend(sender);
            senderUser->addFriend(receiver);
            cout << receiver << " accepted the friend request from " << sender << endl;
        } else {
            cout << "No friend request from " << sender << " to " << receiver << endl;
        }
    } else {
        cout << "One or both users not found!" << endl;
    }
}

void FriendRequestManager::rejectRequest(const string& receiver, const string& sender) {
    User* receiverUser = User::getUserByUsername(receiver);

    if (receiverUser) {
        if (!receiverUser->friendRequests.empty() && receiverUser->friendRequests.front() == sender) {
            receiverUser->friendRequests.pop();
            cout << receiver << " rejected the friend request from " << sender << endl;
        } else {
            cout << "No friend request from " << sender << " to " << receiver << endl;
        }
    } else {
        cout << "Receiver user not found!" << endl;
    }
}
