#include "BookmarkManager.h"

BookmarkManager::BookmarkManager(const std::vector<Bookmark> bookmarks)
	: bookmarks(bookmarks) {}
BookmarkManager::~BookmarkManager() {}
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
std::vector<Bookmark> BookmarkManager::getBookmarksByTag(const std::string& tag) {
	std::vector<Bookmark> result;
	for (const auto& bookmark : bookmarks) {
		if (bookmark.hasTag(tag)) {
			result.push_back(bookmark);
		}
	}
	return result;
}
bool BookmarkManager::serialize(std::ofstream& out) {
	if (!out.is_open()) {
		return false;
	}
	out << bookmarks.size() << "\n"; 
	for (auto& bookmark : bookmarks) { 
		if (!bookmark.serialize(out)) {
			return false; 
		}
	}
	return true; 
}
bool BookmarkManager::deserialize(std::ifstream& in) {
	if (!in.is_open()) {
		return false;
	}
	size_t numBookmarks;
	in >> numBookmarks;
	bookmarks.clear(); 
	bookmarks.reserve(numBookmarks); 
	for (size_t i = 0; i < numBookmarks; ++i) {
		Bookmark bookmark = Bookmark::create(WebPage::create("", "", ""), {  });
		if (!bookmark.deserialize(in)) {
			return false; 
		}
		bookmarks.push_back(bookmark); 
	}
	return true; 
}