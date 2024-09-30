#include "SearchManager.h"

SearchManager::SearchManager(const std::vector<WebPage>& pages) 
	: pages(pages) {}
SearchManager::~SearchManager() {}
SearchManager SearchManager::create(const std::vector<WebPage>& pages) {
	return SearchManager(pages);
}
const bool SearchManager::add(const WebPage& page) {
	pages.push_back(page);
	return true;
}
std::optional<WebPage> SearchManager::findByUrl(const std::string& url) {
	for (const auto& page : pages) {
		if (page.getUrl() == url) {
			return std::make_optional<WebPage>(page);
		}
	}
	return std::nullopt;
}
void SearchManager::loadFromFile(std::ifstream& in) {
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string url, domain, title; 
        if (std::getline(ss, url, ';') && std::getline(ss, domain, ';') && std::getline(ss, title, ';')) {
            WebPage page = WebPage::create(url, domain, title);
            add(page);
        }
    }
}