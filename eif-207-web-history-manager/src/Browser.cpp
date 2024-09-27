#include "Browser.h"

Browser::Browser(const TabManager& tabManager, const BookmarkManager bookmarkManager)
	: tabManager(tabManager), bookmarkManager(bookmarkManager), isPrivate(false) {}
Browser::~Browser() {}
const void Browser::openTab() {
	tabManager.addTab();
}