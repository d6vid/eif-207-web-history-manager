#pragma once

#include "History.h"

class Tab {
public:
	Tab(const History& history = {});
	bool goForward();
	bool goBackward();
	bool setCurrentPage(const WebPage& page);
	std::optional<WebPage> getCurrentPage() const;
	bool hasPages() const;
	~Tab();
private:
	History history;
	std::optional<WebPage> currentPage;
};