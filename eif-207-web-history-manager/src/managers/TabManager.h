#pragma once

#include "Tab.h"
#include <vector>
#include <optional>

class TabManager {
public:
	static TabManager create(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	const bool addTab(const Tab& tab = Tab::create());
	const bool removeTab(const size_t index);
	const std::optional<Tab>& getCurrentTab() const;
	const bool moveToLeftTab();
	const bool moveToRightTab();
	const bool moveToTabByIndex(const size_t index);
	std::vector<Tab> getTabs() const;
	~TabManager();
private:
	TabManager(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	std::vector<Tab> tabs;
	std::optional<size_t> currentTab;
};