#include "PostManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
    Post* newPost = new Post(postId++, content, author, 0);
    PostNode* newNode = new PostNode(newPost);
    newNode->next = head;
    head = newNode;
    cout << "Post created successfully by " << author << "!" << endl;
    PostManager::savePostsForUser(author);
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

bool PostManager::likeSpecificPost(Post* post) { 
    if (post) {
        post->likePost();
        cout << "Post by " << post->author << " liked successfully!" << endl;
        return true;
    }
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

string PostManager::serializePostsForUser(const vector<Post*>& posts) {
    stringstream ss;
    for (const Post* post : posts) {
        ss << post->postId << "|" << post->content << "|" << post->author << "|" << post->likes << "\n";
    }
    return ss.str();
}

vector<Post*> PostManager::deserializePostsForUser(const string& data) {
    vector<Post*> posts;
    stringstream ss(data);
    string line;
    while (getline(ss, line)) {
        stringstream postStream(line);
        string postIdStr, content, author, likesStr;
        getline(postStream, postIdStr, '|');
        getline(postStream, content, '|');
        getline(postStream, author, '|');
        getline(postStream, likesStr);

        int postId = stoi(postIdStr);
        int likes = stoi(likesStr);
        posts.push_back(new Post(postId, content, author, likes));
    }
    return posts;
}

void PostManager::savePostsForUser(const string& username) {
    ofstream outFile("C:/Users/CT/Desktop/semester3/DSA/project/posts_" + username + ".txt");
    if (!outFile.is_open()) {
        cerr << "Error opening file for saving posts!" << endl;
        return;
    }

    vector<Post*> posts = getAllPosts();
    outFile << serializePostsForUser(posts);
    outFile.close();
    cout << "Posts saved for user " << username << "!" << endl;
}

void PostManager::loadPostsForUser(const string& username) {
    ifstream inFile("C:/Users/CT/Desktop/semester3/DSA/project/posts_" + username + ".txt");
    if (!inFile.is_open()) {
        cerr << "Error opening file for loading posts!" << endl;
        return;
    }

    stringstream buffer;
    buffer << inFile.rdbuf();
    vector<Post*> posts = deserializePostsForUser(buffer.str());
    
    for (Post* post : posts) {
        createPost(post->content, post->author);
    }

    inFile.close();
    cout << "Posts loaded for user " << username << "!" << endl;
}
