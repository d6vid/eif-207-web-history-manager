#pragma once

#include "BookmarkManager.h"
#include "TabManager.h"
#include "SearchManager.h"

class Browser {
public:
	Browser(const TabManager& tabManager = TabManager::create(), const BookmarkManager& bookmarkManager = BookmarkManager::create(), 
			const SearchManager& searchManager = SearchManager::create({ WebPage::create("www.una.com", "una.com", "UNA"), WebPage::create("www.facebook.com", "facebook.com", "Facebook") }));
	~Browser();

	// 1. General Management
	const void switchPrivateSearch();
	const bool getIsPrivate();

	// 2. Search Management
	const bool searchPage(const std::string& url);
	const std::optional<WebPage> getPageByUrl(const std::string& url);
	
	// 3. Tab Management
	const std::optional<Tab> getCurrentTab();
	const std::optional<size_t> getCurrentTabIndex();
	const bool openTab();
	const bool closeCurrentTab();
	const bool moveToLeftTab();
	const bool moveToRightTab();

	// 4. History/WebPage Management
	const bool moveToLeftPage();
	const bool moveToRightPage();
	const std::optional<WebPage> getCurrentPage();
	
	// 5. Bookmark Management
	const bool addBookmark(const WebPage& page, const std::vector<std::string>& tags);
	const bool removeBookmarkByIndex(const size_t index);
	const std::vector<Bookmark>& getBookmarks() const;
	std::vector<Bookmark> getBookmarksByTag(const std::string& tag);

private:
	TabManager tabManager;
	BookmarkManager bookmarkManager;
	SearchManager searchManager;
	bool isPrivate;
};