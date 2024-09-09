#pragma once

#include <string>
#include <iostream>

class WebPage {
public:
	WebPage(const std::string& url = "", const std::string& domain = "", const std::string& title = "");
	const std::string& getUrl() const;
	const std::string& getDomain() const;
	const std::string& getTitle() const;
	~WebPage();
private:
	std::string url;
	std::string domain;
	std::string title;
};