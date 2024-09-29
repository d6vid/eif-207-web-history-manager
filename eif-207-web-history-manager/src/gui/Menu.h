#pragma once

#include "Browser.h"
#include <iostream>
#include <Windows.h>

class Menu {
public:
	Menu(Browser&);
	void showMenu();
	void handleOption(int);

private:
	Browser& browser;
	void goToWebsite();
	void addBookmark();
	void searchHistory();
	void importExport();
	void configurePolicies();

};