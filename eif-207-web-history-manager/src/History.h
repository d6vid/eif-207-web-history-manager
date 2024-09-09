#pragma once

#include <deque>
#include <optional>
#include <stdexcept>
#include "WebPage.h"

class History {
public:
	History(const std::deque<WebPage>& visitedPages = {}, int currentIndex = -1);
	bool addPage(const WebPage& webPage);
	std::optional<WebPage> getCurrentPage() const;
	bool moveToLeftPage();
	bool moveToRightPage();
	bool isEmpty() const;
	~History();
private:
	std::deque<WebPage> visitedPages;
	int currentIndex;
};