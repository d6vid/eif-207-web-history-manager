#pragma once

#include "Serializer.h"
#include "WebPage.h"

class WebPageSerializer : public Serializer<WebPage> {
public:
	void save(const WebPage& object, std::ofstream& out) const;
	void load(WebPage& object, std::ifstream& in) const;
};