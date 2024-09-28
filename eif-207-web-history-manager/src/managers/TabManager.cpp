#include "TabManager.h"

TabManager::TabManager(const std::vector<Tab>& tabs, const std::optional<size_t> currentTab)
	: tabs(tabs), currentTab(currentTab) {}
TabManager TabManager::create(const std::vector<Tab>& tabs, const std::optional<size_t> currentTab) {
	if (currentTab && (tabs.size() <= (*currentTab))) {
		throw std::invalid_argument("Invalid argument: currentIndex value must be on bounds.");
	}
	return (!tabs.empty() && !currentTab) ? TabManager(tabs, std::make_optional<size_t>(0)) : TabManager(tabs, currentTab);
}
const bool TabManager::addTab(const Tab& tab) {
	*currentTab = tabs.size();
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
const std::optional<Tab>& TabManager::getCurrentTab() const {
	if (currentTab) {
		return tabs.at(*currentTab);
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
std::vector<Tab> TabManager::getTabs() const {
	return tabs;
}
TabManager::~TabManager() {}