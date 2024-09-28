#pragma once

#include <string>
#include <iostream>
#include <algorithm>

class WebPage {
public:
	static WebPage create(const std::string& url, const std::string& domain, const std::string& title);
	const std::string& getUrl() const;
	const std::string& getDomain() const;
	const std::string& getTitle() const;
	~WebPage();
private:
	WebPage(const std::string& url, const std::string& domain, const std::string& title);
	std::string url;
	std::string domain;
	std::string title;
};