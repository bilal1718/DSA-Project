#include "Post.h"

Post::Post(int postId, const string& content, const string& author)
    : postId(postId), content(content), author(author), likes(0) {}

void Post::likePost() {
    likes++;
}
