#include "Bookmark.h"

Bookmark::Bookmark(const WebPage& page, const std::vector<std::string>& tags) 
	: page(page), tags(tags) {}
Bookmark::~Bookmark() {}
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
bool Bookmark::serialize(std::ofstream& out) {
	page.serialize(out);
	size_t tagCount = tags.size();
	out.write(reinterpret_cast<const char*>(&tagCount), sizeof(tagCount));
	for (const auto& tag : tags) {
		size_t length = tag.size();
		out.write(reinterpret_cast<const char*>(&length), sizeof(length)); 
		out.write(tag.data(), length); 
	}
    return out.good();
}
bool Bookmark::deserialize(std::ifstream& in) {
    page.deserialize(in);
    size_t tagCount;
    in.read(reinterpret_cast<char*>(&tagCount), sizeof(tagCount));
	tags.resize(tagCount);
	for (auto& tag : tags) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length)); 
        tag.resize(length);
        in.read(&tag[0], length); 
    }
    return in.good();
}
std::string Bookmark::toString() const {
	std::string toString = "Pagina Marcada: " + page.getUrl() + "\n"
                           "Etiquetas: ";
	for (auto& tag : tags) {
		toString.append(tag + ", ");
	}
	return toString;
}
