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

bool History::serialize(std::ofstream& out) {
    size_t count = visitedPages.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));
    for (auto& page : visitedPages) {
        if (!page.serialize(out)) {
            return false;  
        }
    }
    out.write(reinterpret_cast<char*>(&currentIndex), sizeof(currentIndex));
    return out.good();
}
bool History::deserialize(std::ifstream& in) {
    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    visitedPages.resize(count);
    for (auto& page : visitedPages) {
        if (!page.deserialize(in)) {
            return false;  
        }
    }
    in.read(reinterpret_cast<char*>(&currentIndex), sizeof(currentIndex));
    return in.good();
}