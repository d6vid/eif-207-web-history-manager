#pragma once

#include <vector>
#include "WebPage.h"

class Bookmark {
public:
    static Bookmark create(const WebPage& page, const std::vector<std::string>& tags);
    const WebPage& getPage() const;
    const std::vector<std::string>& getTags() const;
    const bool hasTag(const std::string& tag) const;
    ~Bookmark();
private:
    Bookmark(const WebPage& page, const std::vector<std::string>& tags);
    WebPage page;
    std::vector<std::string> tags;
};