#include "WebPage.h"
#include "Tab.h"
#include "TabManager.h"
#include "Browser.h"

int main()
{
	// Tab/History Testing (!)
	WebPage p1 = WebPage::create("www.una.com", "una.com", "Universidad Nacional de Costa Rica");
	WebPage p2 = WebPage::create("www.google.com", "google.com", "GOOGLE");
	WebPage p3 = WebPage::create("www.facebook.com", "facebook.com", "Facebook");
	WebPage p4 = WebPage::create("www.instagram.com", "instagram.com", "Instagram");
	WebPage p5 = WebPage::create("www.github.com", "github.com", "Github");
	Tab t1 = Tab::create();
	t1.setCurrentPage(p1);
	t1.setCurrentPage(p2);
	t1.setCurrentPage(p3);
	t1.goBackward();
	t1.goBackward();
	t1.setCurrentPage(p5);
	t1.goBackward();
	t1.goBackward();
	t1.setCurrentPage(p1);
	t1.setCurrentPage(p2);

	Tab t2 = Tab::create();
	t2.setCurrentPage(p5);

	TabManager tm1 = TabManager::create({ t1 });
	tm1.addTab(t2);
	tm1.moveToLeftTab();
	tm1.moveToLeftTab();

	Browser b1 = Browser(tm1);


	return 0;
}


