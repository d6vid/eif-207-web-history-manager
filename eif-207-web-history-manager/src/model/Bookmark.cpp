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
    if (!out.is_open()) return false;

    if (!page.serialize(out)) return false;

    size_t numTags = tags.size();
    out.write(reinterpret_cast<const char*>(&numTags), sizeof(numTags));
    if (!out.good()) return false;

    for (const auto& tag : tags) {
        size_t length = tag.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        if (!out.good()) return false;

        out.write(tag.c_str(), length);
        if (!out.good()) return false;
    }

    return true;
}
bool Bookmark::deserialize(std::ifstream& in) {
    if (!in.is_open()) return false;

    if (!page.deserialize(in)) return false;

    size_t numTags;
    in.read(reinterpret_cast<char*>(&numTags), sizeof(numTags));
    if (!in.good()) return false;

    tags.clear();
    for (size_t i = 0; i < numTags; ++i) {
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (!in.good()) return false;

        std::string tag(length, '\0');
        in.read(&tag[0], length);
        if (!in.good()) return false;

        tags.push_back(tag);
    }

    return true;
}
std::string Bookmark::toString() const {
	std::string toString = "Pagina Marcada: " + page.getUrl() + "\n"
                           "Etiquetas: ";
	for (auto& tag : tags) {
		toString.append(tag + ", ");
	}
	return toString;
}