#ifndef POST_H
#define POST_H

#include <string>
using namespace std;

class Post {
private:
    string username;
    string content;
    int likes;

public:
    Post(const string& user, const string& text)
        : username(user), content(text), likes(0) {}

    Post() : username(""), content("[No content]"), likes(0) {}

    const string& getUsername() const { return username; }
    const string& getContent() const { return content; }
    int getLikes() const { return likes; }

    void addLike() { likes++; }

    void editContent(const string& newContent) {
        content = newContent;
    }

    void deletePost() {
        content = "[Post deleted]";
    }
};

#endif
