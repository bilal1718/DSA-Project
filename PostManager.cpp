#include "PostManager.h"
#include <iostream>
using namespace std;

PostManager::PostManager() : head(nullptr) {}

PostManager::~PostManager() {
    while (head) {
        PostNode* temp = head;
        head = head->next;
        delete temp->post;
        delete temp;
    }
}

void PostManager::createPost(const string& content, const string& author) {
    static int postId = 1;
    Post* newPost = new Post(postId++, content, author);
    PostNode* newNode = new PostNode(newPost);
    newNode->next = head;
    head = newNode;
    cout << "Post created successfully by " << author << "!" << endl;
}

vector<Post*> PostManager::getAllPosts() const {
    vector<Post*> posts;
    PostNode* current = head;
    while (current) {
        posts.push_back(current->post);
        current = current->next;
    }
    return posts;
}
