#include "WebPage.h"
#include "WebPageSerializer.h"
#include <fstream>

int main()
{
	const WebPageSerializer ps1 = WebPageSerializer();

	std::ofstream wf("../../../../eif-207-web-history-manager/files/states/page.dat", std::ios::out | std::ios::binary);
	if (!wf) {
		std::cout << "Cannot open file!" << std::endl;
		return 0;
	}
	const WebPage p1 = WebPage::create("www.facebook.com", "facebook.com", "Facebook");
	ps1.save(p1, wf);

	std::ifstream rf("../../../../eif-207-web-history-manager/files/states/page.dat", std::ios::out | std::ios::binary);
	if (!rf) {
		std::cout << "Cannot open file!" << std::endl;
		return 1;
	}
	WebPage p2 = WebPage::create("", "", "");
	ps1.load(p2, rf);

	std::cout << p2.getTitle();

	return 0;
}