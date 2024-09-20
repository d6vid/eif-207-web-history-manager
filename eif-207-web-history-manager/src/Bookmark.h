#pragma once

#include <vector>
#include "WebPage.h"

class BookmarkSystem {
public:
    BookmarkSystem();
    void addBookmark(const WebPage& page);
    void removeBookmark(const std::string& url);
    bool isBookmarked(const std::string& url) const;
    std::vector<WebPage> getBookmarks() const;

private:
    std::vector<WebPage> bookmarks; 
};


