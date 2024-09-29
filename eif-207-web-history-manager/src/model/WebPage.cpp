#include "WebPage.h"

WebPage::WebPage() {}
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
bool WebPage::serialize(std::ofstream& out) {
	size_t urlLength = url.size();
	out.write(reinterpret_cast<const char*>(&urlLength), sizeof(urlLength));
	out.write(url.c_str(), urlLength);
	size_t domainLength = domain.size();
	out.write(reinterpret_cast<const char*>(&domainLength), sizeof(domainLength));
	out.write(domain.c_str(), domainLength);
	size_t titleLength = title.size();
	out.write(reinterpret_cast<const char*>(&titleLength), sizeof(titleLength));
	out.write(title.c_str(), titleLength);
	return out.good();  
}
bool WebPage::deserialize(std::ifstream & in) {
	size_t urlLength;
	in.read(reinterpret_cast<char*>(&urlLength), sizeof(urlLength));
	url.resize(urlLength);
	in.read(&url[0], urlLength);
	size_t domainLength;
	in.read(reinterpret_cast<char*>(&domainLength), sizeof(domainLength));
	domain.resize(domainLength);
	in.read(&domain[0], domainLength);
	size_t titleLength;
	in.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
	title.resize(titleLength);
	in.read(&title[0], titleLength);
	return in.good();
}