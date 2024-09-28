#include "Bookmark.h"

Bookmark::Bookmark(const WebPage& page, const std::vector<std::string>& tags) 
	: page(page), tags(tags) {}
Bookmark Bookmark::create(const WebPage& page, const std::vector<std::string>& tags) {
	return Bookmark(page, tags);
}
const WebPage& Bookmark::getPage() const {
	return page;
}
const std::vector<std::string>& Bookmark::getTags() const {
	return tags;
}
const bool Bookmark::hasTag(const std::string& tag) const {
	return std::find(tags.begin(), tags.end(), tag) != tags.end();
}
Bookmark::~Bookmark() {}
