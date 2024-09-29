#include "TabManager.h"

TabManager::TabManager(const std::vector<Tab>& tabs, const std::optional<size_t> currentTab)
	: tabs(tabs), currentTab(currentTab), isPrivate(false) {}
TabManager::~TabManager() {}
TabManager TabManager::create(const std::vector<Tab>& tabs, const std::optional<size_t> currentTab) {
	if (currentTab && (tabs.size() <= (*currentTab))) {
		throw std::invalid_argument("Invalid argument: currentIndex value must be on bounds.");
	}
	return (!tabs.empty() && !currentTab) ? TabManager(tabs, std::make_optional<size_t>(0)) : TabManager(tabs, currentTab);
}
const bool TabManager::addTab(const Tab& tab) {
	currentTab = std::make_optional<size_t>(tabs.size());
	tabs.push_back(tab);
	return true;
}
const bool TabManager::removeTab(const size_t index) {
	if (index >= 0 && index < tabs.size()) {
		tabs.erase(tabs.begin() + index);
		return true;
	}
	return false;
}
const bool TabManager::removeCurrentTab() {
	if (!tabs.empty() && currentTab) {
		size_t indexToDelete = *currentTab;
		currentTab = ((*currentTab) != 0) ? std::make_optional<size_t>((*currentTab) - 1) : std::nullopt;
		tabs.erase(tabs.begin() + indexToDelete);
		return true;
	}
	return false;
}
const std::optional<Tab> TabManager::getCurrentTab() {
	if (currentTab) {
		return tabs.at(*currentTab);
	}
	return std::nullopt;
}
const std::optional<size_t> TabManager::getCurrentTabIndex() {
	if (currentTab) {
		return currentTab;
	}
	return std::nullopt;
}
const bool TabManager::moveToLeftTab() {
	if (currentTab && ((*currentTab) > 0)) {
		(*currentTab)--;
		return true;
	}
	return false;
}
const bool TabManager::moveToRightTab() {
	if (currentTab && ((*currentTab) < tabs.size()-1)) {
		(*currentTab)++;
		return true;
	}
	return false;
}
const bool TabManager::moveToTabByIndex(const size_t index) {
	if (!tabs.empty() && (index >= 0 && index < tabs.size())) {
		*currentTab = index;
		return true;
	}
	return false;
}
const bool TabManager::moveToLastTab() {
	if (!tabs.empty()) {
		*currentTab = tabs.size()-1;
		return true;
	}
	return false;
}
const bool TabManager::moveCurrentTabToLeftPage() {
	if (currentTab) {
		return tabs.at(*currentTab).goBackward();
	}
	return false;
}
const bool TabManager::moveCurrentTabToRightPage() {
	if (currentTab) {
		return tabs.at(*currentTab).goForward();
	}
	return false;
}
const bool TabManager::addPageToTab(const WebPage& page) {
	if (currentTab) {
		return tabs.at(*currentTab).setCurrentPage(page, !isPrivate);
	}
	return false;
}
void TabManager::switchHistoryTracking(const bool state) {
	isPrivate = state;
}