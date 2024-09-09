#pragma once

#include <list>
#include <optional>
#include <stdexcept>
#include "WebPage.h"

class History {
public:
	History(const std::list<WebPage>& visitedPages = {}, int currentIndex = 0);
	bool addPage(const WebPage& webPage);
	std::optional<WebPage> getCurrentPage() const;
	bool moveToLeftPage();
	bool moveToRightPage();
	bool isEmpty() const;
	~History();
private:
	std::list<WebPage> visitedPages;
	int currentIndex;
};