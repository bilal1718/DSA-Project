#ifndef POST_MANAGER_H
#define POST_MANAGER_H

#include "Post.h"
#include <vector>

struct PostNode {
    Post* post;
    PostNode* next;

    PostNode(Post* post) : post(post), next(nullptr) {}
};

class PostManager {
private:
    PostNode* head;

public:
    PostManager();
    ~PostManager();
    void createPost(const string& content, const string& author);
    vector<Post*> getAllPosts() const;
};

#endif
