#pragma once

#include <vector>
#include "Bookmark.h"

class BookmarkManager {
public:
    static BookmarkManager create(const std::vector<Bookmark> bookmarks = {});
    const bool addBookmark(const Bookmark& bookmark);
    const bool removeBookmark(const int index);
    const std::vector<Bookmark>& getBookmarks() const;
    std::vector<Bookmark> getBookmarksByTag(const std::string& tag);
    ~BookmarkManager();
private:
    BookmarkManager(const std::vector<Bookmark> bookmarks = {});
    std::vector<Bookmark> bookmarks;
};