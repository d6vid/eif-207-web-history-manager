#pragma once

#define NOMINMAX

#include "Browser.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sstream>
#include <limits>

class BrowserController {
public:
	BrowserController();
	void showMenu();
	void handleMenuOption();
private:
	Browser browser;
	void goToWebsite();
	void openTab();
	void addBookmark();
	void showAndSelectBookmark();
	void switchIncognito();
	/*
	void importExport();
	void configurePolicies();
	*/
};