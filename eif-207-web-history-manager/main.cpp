#include "WebPage.h"
#include "BrowserController.h"

int main()
{
	BrowserController app;
	while (true) {
		app.showMenu();
		app.handleMenuOption();
	}
	return 0;
}