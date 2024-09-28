#pragma once

#include "History.h"

class Tab {
public:
	static Tab create(const History& history = History::create());
	bool goForward();
	bool goBackward();
	bool setCurrentPage(const WebPage& page);
	std::optional<WebPage> getCurrentPage() const;
	bool hasPages() const;
	const History& getHistory() const;
	~Tab();
private:
	Tab(const History& history = History::create(), const std::optional<WebPage>& currentPage = std::nullopt);
	History history;
	std::optional<WebPage> currentPage;
};