#pragma once

#include <deque>
#include <optional>
#include <stdexcept>
#include "WebPage.h"
#include "Serializable.h"

class History : public Serializable {
public:
	static History create(const std::deque<WebPage>& visitedPages = {}, std::optional<size_t> currentIndex = std::nullopt);
	bool addPage(const WebPage& webPage);
	const std::optional<WebPage> getCurrentPage() const;
	const std::deque<WebPage>& getVisitedPages() const;
	bool moveToLeftPage();
	bool moveToRightPage();
	bool isEmpty() const;
	bool serialize(std::ofstream& out);
	bool deserialize(std::ifstream& in);
	~History();
private:
	History(const std::deque<WebPage>& visitedPages = {}, std::optional<size_t> currentIndex = std::nullopt);
	std::deque<WebPage> visitedPages;
	std::optional<size_t> currentIndex;
};