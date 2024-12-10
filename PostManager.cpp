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

bool PostManager::likePost(int postId) {
    PostNode* current = head;
    while (current) {
        if (current->post->postId == postId) {
            current->post->likePost();
            cout << "Post with ID " << postId << " liked successfully!" << endl;
            return true;
        }
        current = current->next;
    }
    cout << "Post with ID " << postId << " not found!" << endl;
    return false;
}

vector<Post*> PostManager::viewTrendingPosts() const {
    vector<Post*> posts = getAllPosts();
    
    for (size_t i = 0; i < posts.size() - 1; i++) {
        for (size_t j = 0; j < posts.size() - i - 1; j++) {
            if (posts[j]->likes < posts[j + 1]->likes) {
                swap(posts[j], posts[j + 1]);
            }
        }
    }

    return posts;
}
