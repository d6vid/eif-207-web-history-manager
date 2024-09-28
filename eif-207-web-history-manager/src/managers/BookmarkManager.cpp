#include "BookmarkManager.h"

BookmarkManager::BookmarkManager(const std::vector<Bookmark> bookmarks)
	: bookmarks(bookmarks) {}
BookmarkManager BookmarkManager::create(const std::vector<Bookmark> bookmarks) {
	return BookmarkManager(bookmarks);
}
const bool BookmarkManager::addBookmark(const Bookmark& bookmark) {
	bookmarks.push_back(bookmark);
	return true;
}
const bool BookmarkManager::removeBookmark(const int index) {
	if (index < bookmarks.size()) {
		bookmarks.erase(bookmarks.begin() + index);
		return true;
	}
	return false;
}
const std::vector<Bookmark>& BookmarkManager::getBookmarks() const {
	return bookmarks;
}
const std::vector<Bookmark> BookmarkManager::getBookmarksByTag(const std::string& tag) const {
	std::vector<Bookmark> result = {};
	for (const auto& bookmark : bookmarks) {
		if (bookmark.hasTag(tag)) {
			result.push_back(bookmark);
		}
	}
	return result;
}
BookmarkManager::~BookmarkManager() {}