#include "SearchManager.h"

SearchManager::SearchManager(const std::vector<WebPage>& pages = {}) 
	: pages(pages) {}
SearchManager::~SearchManager() {}
SearchManager SearchManager::create(const std::vector<WebPage>& pages) {
	return SearchManager(pages);
}
const bool SearchManager::add(const WebPage& page) {
	pages.push_back(page);
	return true;
}
const std::optional<WebPage> SearchManager::findByUrl(const std::string& url) const {
	for (const auto& page : pages) {
		if (page.getUrl() == url) {
			return std::make_optional<WebPage>(page);
		}
	}
	return std::nullopt;
}