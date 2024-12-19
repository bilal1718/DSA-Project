#ifndef POST_MANAGER_H
#define POST_MANAGER_H

#include "Post.h"
#include <vector>
#include <string>

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

    void createPost(const std::string& content, const std::string& author);
    std::vector<Post*> getAllPosts() const;
    void savePostsForUser(const std::string& username); 
    void loadPostsForUser(const std::string& username);

    bool likePost(int postId);
    bool likeSpecificPost(Post* post);
    std::vector<Post*> viewTrendingPosts() const;
     std::string serializePostsForUser(const std::vector<Post*>& posts);
    std::vector<Post*> deserializePostsForUser(const std::string& username);
};

#endif
