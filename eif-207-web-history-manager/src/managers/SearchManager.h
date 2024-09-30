#pragma once

#include <vector>
#include <optional>
#include <sstream>
#include "WebPage.h"

class SearchManager {
public:
	static SearchManager create(const std::vector<WebPage>& pages);
	const bool add(const WebPage& page);
	std::optional<WebPage> findByUrl(const std::string& url);
	void loadFromFile(std::ifstream& in);
	~SearchManager();
private:
	SearchManager(const std::vector<WebPage>& pages = {});
	std::vector<WebPage> pages;
};