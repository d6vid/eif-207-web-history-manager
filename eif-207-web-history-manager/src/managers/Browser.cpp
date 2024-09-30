#include "Browser.h"

Browser::Browser(const TabManager& tabManager, const BookmarkManager& bookmarkManager, const SearchManager& searchManager)
	: tabManager(tabManager), bookmarkManager(bookmarkManager), searchManager(searchManager), isPrivate(false) {}
Browser::~Browser() {}

// X. Policies
const void Browser::applyPolicies() {
	tabManager.applyPolicies();
}

// 1. General Management
const void Browser::switchPrivateSearch() {
	isPrivate = !isPrivate;
	tabManager.switchHistoryTracking(isPrivate);
}
const bool Browser::getIsPrivate() {
	return isPrivate;
}

// 2. Search Management
const bool Browser::searchPage(const std::string& url) {
	const std::optional<WebPage> page = searchManager.findByUrl(url);
	if (page) {
		return tabManager.addPageToTab(*page);
	}
	return false;
}
const std::optional<WebPage> Browser::getPageByUrl(const std::string& url) {
	return searchManager.findByUrl(url);
}
const void Browser::loadPagesFromFile(std::ifstream& in) {
	searchManager.loadFromFile(in);
}

// 3. Tab Management
const std::optional<Tab> Browser::getCurrentTab() {
	return tabManager.getCurrentTab();
}
const std::optional<size_t> Browser::getCurrentTabIndex() {
	return tabManager.getCurrentTabIndex();
}
const bool Browser::openTab() {
	if (tabManager.addTab()) {
		return tabManager.moveToLastTab();
	}
	return false;
}
const bool Browser::closeCurrentTab() {
	return tabManager.removeCurrentTab();
}
const bool Browser::moveToLeftTab() {
	return tabManager.moveToLeftTab();
}
const bool Browser::moveToRightTab() {
	return tabManager.moveToRightTab();
}

// 4. History/WebPage Management
const bool Browser::moveToLeftPage() {
	return tabManager.moveCurrentTabToLeftPage();
}
const bool Browser::moveToRightPage() {
	return tabManager.moveCurrentTabToRightPage();
}
const std::optional<WebPage> Browser::getCurrentPage() {
	const std::optional<Tab> currentTab = tabManager.getCurrentTab();
	if (currentTab) {
		return (*currentTab).getCurrentPage();
	}
	return std::nullopt;
}

// 5. Bookmark Management
const bool Browser::addBookmark(const WebPage& page, const std::vector<std::string>& tags) {
	Bookmark newBookmark = Bookmark::create(page, tags);
	return bookmarkManager.addBookmark(newBookmark);
}
const bool Browser::removeBookmarkByIndex(const size_t index) {
	return bookmarkManager.removeBookmark(index);
}
const std::vector<Bookmark>& Browser::getBookmarks() const {
	return bookmarkManager.getBookmarks();
}
std::vector<Bookmark> Browser::getBookmarksByTag(const std::string& tag) {
	return bookmarkManager.getBookmarksByTag(tag);
}

// 6. Data Persistance
bool Browser::serialize(std::ofstream& out) {
	if (!out.is_open()) {
		return false;
	}
	out << isPrivate << "\n";
	if (!tabManager.serialize(out)) {
		return false;
	}
	if (!bookmarkManager.serialize(out)) {
		return false;
	}
	return true; 
}
bool Browser::deserialize(std::ifstream& in) {
	if (!in.is_open()) {
		return false;
	}
	in >> isPrivate;
	if (!tabManager.deserialize(in)) {
		return false;
	}
	//if (!bookmarkManager.deserialize(in)) {
	//	return false;
	//}
	return true; 
}