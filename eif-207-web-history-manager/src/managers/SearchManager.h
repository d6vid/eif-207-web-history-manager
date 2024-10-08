#pragma once

#include <vector>
#include <optional>
#include "WebPage.h"

class SearchManager {
public:
	static SearchManager create(const std::vector<WebPage>& pages);
	const bool add(const WebPage& page);
	const std::optional<WebPage> findByUrl(const std::string& url) const;
	~SearchManager();
private:
	SearchManager(const std::vector<WebPage>& pages = {});
	std::vector<WebPage> pages;
};