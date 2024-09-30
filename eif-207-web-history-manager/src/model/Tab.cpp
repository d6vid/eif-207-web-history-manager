#include "Tab.h"

Tab::Tab(const History& history, const std::optional<WebPage>& currentPage) 
	: history(history), currentPage(currentPage) {}
Tab::~Tab() {}
Tab Tab::create(const History& history) {
	return Tab(history, history.getCurrentPage());
}
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
bool Tab::setCurrentPage(const WebPage& page, const bool track) {
	if (track) {
		if (history.addPage(page)) {
			currentPage = std::make_optional<WebPage>(page);
			return true;
		}
	}
	else {
		currentPage = std::make_optional<WebPage>(page);
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

const History& Tab::getHistory() const {
	return history;
}
bool Tab::serialize(std::ofstream& out) {
	bool hasCurrentPage = currentPage.has_value();
	out << hasCurrentPage;
	if (hasCurrentPage) {
		currentPage->serialize(out);
	}
	history.serialize(out);
	return out.good();
}
bool Tab::deserialize(std::ifstream& in) {
	bool hasCurrentPage;
	in >> hasCurrentPage;
	if (hasCurrentPage) {
		WebPage page;
		if (!page.deserialize(in)) {
			return false; 
		}
		currentPage = page;
	}
	else {
		currentPage.reset();
	}
	if (!history.deserialize(in)) {
		return false; 
	}

	return in.good(); // Return true if all operations were successful
}
