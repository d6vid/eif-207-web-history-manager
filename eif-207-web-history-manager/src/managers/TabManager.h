#pragma once

#include "Tab.h"
#include <vector>
#include <optional>

class TabManager : public Serializable {
public:
	static TabManager create(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	const bool addTab(const Tab& tab = Tab::create());
	const bool removeTab(const size_t index);
	const bool removeCurrentTab();
	const std::optional<Tab> getCurrentTab();
	const std::optional<size_t> getCurrentTabIndex();
	const bool moveToLeftTab();
	const bool moveToRightTab();
	const bool moveToTabByIndex(const size_t index);
	const bool moveToLastTab();
	const bool moveCurrentTabToLeftPage();
	const bool moveCurrentTabToRightPage();
	const bool addPageToTab(const WebPage& page);
	void switchHistoryTracking(const bool state);
	bool serialize(std::ofstream& out);
	bool deserialize(std::ifstream& in);
	~TabManager();
private:
	TabManager(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	std::vector<Tab> tabs;
	std::optional<size_t> currentTab;
	bool isPrivate;
};