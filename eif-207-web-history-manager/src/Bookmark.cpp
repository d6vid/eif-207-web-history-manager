#include "BookmarkSystem.h"

BookmarkSystem::BookmarkSystem() {
}
void BookmarkSystem::addBookmark(const WebPage& page) {
    if (!isBookmarked(page.getUrl())) {
        bookmarks.push_back(page);
    }
}
void BookmarkSystem::removeBookmark(const std::string& url) {
    bookmarks.erase(
        std::remove_if(bookmarks.begin(), bookmarks.end(),
            [&url](const WebPage& page) { return page.getUrl() == url; }),
        bookmarks.end()
    );
}
bool BookmarkSystem::isBookmarked(const std::string& url) const {
    for (const auto& page : bookmarks) {
        if (page.getUrl() == url) {
            return true;
        }
    }
    return false;
}
std::vector<WebPage> BookmarkSystem::getBookmarks() const {
    return bookmarks;
}
