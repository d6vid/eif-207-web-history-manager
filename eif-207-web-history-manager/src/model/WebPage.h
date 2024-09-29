#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Serializable.h"

class WebPage : public Serializable {
public:
	static WebPage create(const std::string& url, const std::string& domain, const std::string& title);
	const std::string& getUrl() const;
	const std::string& getDomain() const;
	const std::string& getTitle() const;
	bool serialize(std::ofstream& out);
	bool deserialize(std::ifstream& in);
	WebPage();
	~WebPage();
private:
	WebPage(const std::string& url, const std::string& domain, const std::string& title);
	std::string url;
	std::string domain;
	std::string title;
};