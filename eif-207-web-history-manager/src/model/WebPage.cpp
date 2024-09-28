#include "WebPage.h"

WebPage::WebPage(const std::string& url, const std::string& domain, const std::string& title)
	: url(url), domain(domain), title(title) {}
WebPage WebPage::create(const std::string& url, const std::string& domain, const std::string& title) {
	return WebPage(url, domain, title);
}
WebPage::~WebPage() {}
const std::string& WebPage::getUrl() const {
	return url;
}
const std::string& WebPage::getDomain() const {
	return domain;
}
const std::string& WebPage::getTitle() const {
	return title;
}