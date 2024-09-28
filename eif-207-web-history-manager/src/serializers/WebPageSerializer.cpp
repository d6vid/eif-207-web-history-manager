#include "WebPageSerializer.h"

void WebPageSerializer::save(const WebPage& object, std::ofstream& out) const {
	out.write((char*)&object, sizeof(WebPage));
	out.close();
	if (!out.good()) {
		std::cout << "ERROR: Error occurred at writing time!" << std::endl;
		return;
	}
}
void WebPageSerializer::load(WebPage& object, std::ifstream& in) const {
	in.read((char*)&object, sizeof(WebPage));
	in.close();
	if (!in.good()) {
		std::cout << "ERROR: Error occurred at reading time!" << std::endl;
	}
}