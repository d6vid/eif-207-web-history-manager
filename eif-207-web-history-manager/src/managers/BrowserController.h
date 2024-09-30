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
	void start();
	BrowserController();
private:
	Browser browser;
	
	// -> General Purpose
	void showMenu();
	void handleMenuOption();

	// -> Search Management
	void goToWebsite();

	// -> Tab Management
	void openTab();

	// -> Bookmark Management
	void addBookmark();
	void showAndSelectBookmark();

	// -> Security Management
	void switchIncognito();

	// -> Data Persistance
	void importPages();
	void importExportSelectMenu();
	std::string importMenu();
	std::string exportMenu();
	void exportSession();
	void importSession();
	
	/*
	void configurePolicies();
	*/
};