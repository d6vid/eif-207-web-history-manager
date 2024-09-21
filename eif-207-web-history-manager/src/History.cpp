#include "History.h"

History::History(const std::deque<WebPage>& visitedPages, int currentIndex)
    : visitedPages(visitedPages), currentIndex(currentIndex) {}
History::~History() {}
bool History::addPage(const WebPage& webPage) {
    if (currentIndex < visitedPages.size() - 1) {
        visitedPages.erase(visitedPages.begin() + currentIndex + 1, visitedPages.end());
    }
    visitedPages.push_back(webPage);
    currentIndex = visitedPages.size() - 1;
    return true;
}
std::optional<WebPage> History::getCurrentPage() const {
    if (isEmpty() || currentIndex < 0) {
        return std::nullopt;
    }
    return visitedPages[currentIndex];
}
bool History::moveToLeftPage() {
    if (currentIndex > -1) {
        --currentIndex;
        return true;
    }
    return false;
}
bool History::moveToRightPage() {
    if (currentIndex < visitedPages.size() - 1) {
        ++currentIndex;
        return true;
    }
    return false;
}
bool History::isEmpty() const {
    return visitedPages.empty();
}

void History::mostrarHistorial() const {
    for (const auto& pagina : visitedPages) {
        std::cout << pagina.getUrl() << " - " << pagina.getTitle();
    }
}