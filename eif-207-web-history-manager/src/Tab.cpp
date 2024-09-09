#include "Tab.h"

Tab::Tab(const History& history) 
	: history(history), currentPage(history.getCurrentPage()) {}
Tab::~Tab() {}
bool Tab::goForward() {
	if (history.moveToRightPage()) {
		currentPage = history.getCurrentPage();
		return true;
	}
	return false;
}
bool Tab::goBackward() {
	if (history.moveToLeftPage()) {
		currentPage = history.getCurrentPage();
		return true;
	}
	return false;
}
bool Tab::setCurrentPage(const WebPage& page) {
	if (history.addPage(page)) {
		currentPage = history.getCurrentPage();
		return true;
	}
	return false;
}
std::optional<WebPage> Tab::getCurrentPage() const {
	return currentPage;
}
bool Tab::hasPages() const {
	return !history.isEmpty();
}