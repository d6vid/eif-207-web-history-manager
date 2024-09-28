#pragma once

#include "BookmarkManager.h"
#include "TabManager.h"
#include "SearchManager.h"

class Browser {
public:
	Browser(const TabManager& tabManager = TabManager::create(), const BookmarkManager bookmarkManager = BookmarkManager::create());
	~Browser();

	// 1. General Management
	const void switchPrivateSearch();

	// 2. Search Management
	const bool searchPage(const std::string& url);
	
	// 3. Tab Management
	const bool openTab();
	const bool closeCurrentTab();
	const bool closeTabByIndex(const size_t index);
	const bool moveToLeftTab();
	const bool moveToRightTab();
	const bool moveToTabByIndex(const size_t index);

	// 4. History/WebPage Management
	const bool moveToLeftPage();
	const bool moveToRightPage();
	const WebPage& getCurrentPage();
	
	// 5. Bookmark Management
	const bool addBookmark(const WebPage& page, const std::vector<std::string>& tags);
	const bool removeBookmarkByIndex(const size_t index);
	const std::string getBookmarksByTag(const std::string& tag) const;

private:
	TabManager tabManager;
	BookmarkManager bookmarkManager;
	bool isPrivate;
};