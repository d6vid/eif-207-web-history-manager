#include "History.h"

History::History(const std::deque<WebPage>& visitedPages, std::optional<size_t> currentIndex)
    : visitedPages(visitedPages), currentIndex(currentIndex) {  }
History::~History() {}
History History::create(const std::deque<WebPage>& visitedPages, std::optional<size_t> currentIndex) {
    if (currentIndex && (visitedPages.size() <= currentIndex)) {
        throw std::invalid_argument("Invalid argument: currentIndex value must be on bounds.");
    }
    return History(visitedPages, currentIndex);
}
bool History::addPage(const WebPage& webPage) {
    if (currentIndex && ((*currentIndex) < visitedPages.size() - 1)) {
        visitedPages.erase(visitedPages.begin() + (*currentIndex) + 1, visitedPages.end());
    }
    visitedPages.push_back(webPage);
    currentIndex = std::make_optional<size_t>(visitedPages.size() - 1);
    return true;
}
const std::optional<WebPage> History::getCurrentPage() const {
    if (isEmpty() || !currentIndex) {
        return std::nullopt;
    }
    return std::make_optional<WebPage>(visitedPages.at(*currentIndex));
}
bool History::moveToLeftPage() {
    if (currentIndex && (*currentIndex) > 0) {
        (*currentIndex)--;
        return true;
    }
    return false;
}
bool History::moveToRightPage() {
    if ((*currentIndex) < visitedPages.size() - 1) {
        (*currentIndex)++;
        return true;
    }
    return false;
}
bool History::isEmpty() const {
    return visitedPages.empty();
}

const std::deque<WebPage>& History::getVisitedPages() const {
    return visitedPages;
}
std::vector<std::string> History::toStringVector() const {
    std::vector<std::string> result;
    for (const auto& webPage : visitedPages) {
        result.push_back(webPage.getUrl()); 
    }
    return result;
}