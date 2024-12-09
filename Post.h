#ifndef POST_H
#define POST_H

#include <string>
using namespace std;

class Post {
public:
    int postId;
    string content;
    string author;
    int likes;

    Post(int postId, const string& content, const string& author);

    void likePost();
};

#endif
