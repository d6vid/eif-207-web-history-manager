#include "History.h"

History::History(const std::list<WebPage>& visitedPages, int currentIndex)
	: visitedPages(visitedPages), currentIndex(currentIndex) {}
History::~History() {}
bool History::addPage(const WebPage& webPage) {
	if (currentIndex != visitedPages.size() - 1) {
		auto it = visitedPages.begin();
		std::advance(it, currentIndex);
		visitedPages.erase(it, visitedPages.end());
	}
	visitedPages.push_back(webPage);
	currentIndex = visitedPages.size() - 1;
	return true;
}
std::optional<WebPage> History::getCurrentPage() const {
	if (currentIndex > 0) {
		auto it = visitedPages.begin();
		std::advance(it, currentIndex);
		return *it;
	}
	return std::nullopt;
}
bool History::moveToLeftPage() {
	if (!visitedPages.empty() && currentIndex != 0) {
		currentIndex--;
		return true;
	}
	return false;
}
bool History::moveToRightPage() {
	if (!visitedPages.empty() && currentIndex != visitedPages.size() - 1) {
		currentIndex++;
		return true;
	}
	return false;
}
bool History::isEmpty() const {
	return visitedPages.empty();
}