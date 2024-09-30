#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <chrono>
#include "../model/WebPage.h"  
#include "../model/History.h"
#include "../model/Bookmark.h"
#include "../model/Tab.h"
#include "../managers/TabManager.h"
#include "../managers/Browser.h"
#include "../managers/BookmarkManager.h"
#include "../managers/SearchManager.h"

namespace Tests {

    int TestWebPageConstructor(const std::string& url, const std::string& domain, const std::string& title) {
        WebPage page = WebPage::create(url, domain, title);

        if (page.getUrl() != url || page.getDomain() != domain || page.getTitle() != title) {
            std::cerr << "TestWebPageConstructor failed." << std::endl;
            return 1;
        }

        std::cout << "TestWebPageConstructor passed." << std::endl;
        return 0;
    }

    int TestBookmarkCreate(const std::string& url, const std::string& domain, const std::string& title, const std::vector<std::string>& tags) {
        WebPage page = WebPage::create(url, domain, title);
        Bookmark bookmark = Bookmark::create(page, tags);

        if (bookmark.getPage().getUrl() != url || bookmark.getTags() != tags) {
            std::cerr << "TestBookmarkCreate failed." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkCreate passed." << std::endl;
        return 0;
    }
    int TestBookmarkHasTag(const std::string& url, const std::string& domain, const std::string& title, const std::vector<std::string>& tags, const std::string& tagToCheck) {
        WebPage page = WebPage::create(url, domain, title);
        Bookmark bookmark = Bookmark::create(page, tags);

        bool hasTag = bookmark.hasTag(tagToCheck);
        bool expectedResult = std::find(tags.begin(), tags.end(), tagToCheck) != tags.end();

        if (hasTag != expectedResult) {
            std::cerr << "TestBookmarkHasTag failed." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkHasTag passed." << std::endl;
        return 0;
    }
    int TestHistoryConstructor(const std::string& url1, const std::string& domain1, const std::string& title1,
        const std::string& url2, const std::string& domain2, const std::string& title2) {
        std::deque<WebPage> pages = {
            WebPage::create(url1, domain1, title1),
            WebPage::create(url2, domain2, title2)
        };

        History history = History::create(pages);

        if (!history.getCurrentPage() || history.getCurrentPage()->getUrl() != url2) {
            std::cerr << "TestHistoryConstructor failed." << std::endl;
            return 1;
        }

        std::cout << "TestHistoryConstructor passed." << std::endl;
        return 0;
    }

    // Test adding a page to History
    int TestHistoryAddPage(const std::string& url1, const std::string& domain1, const std::string& title1,
        const std::string& url2, const std::string& domain2, const std::string& title2) {
        History history = History::create();
        WebPage page1 = WebPage::create(url1, domain1, title1);
        WebPage page2 = WebPage::create(url2, domain2, title2);

        history.addPage(page1);
        history.addPage(page2);

        if (!history.getCurrentPage() || history.getCurrentPage()->getUrl() != url2) {
            std::cerr << "TestHistoryAddPage failed." << std::endl;
            return 1;
        }

        std::cout << "TestHistoryAddPage passed." << std::endl;
        return 0;
    }
    int TestBookmarkManagerCreate() {
        BookmarkManager manager = BookmarkManager::create();

        if (!manager.getBookmarks().empty()) {
            std::cerr << "TestBookmarkManagerCreate failed." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkManagerCreate passed." << std::endl;
        return 0;
    }

    // Test adding a bookmark to BookmarkManager
    int TestBookmarkManagerAddBookmark(const std::string& url, const std::string& domain, const std::string& title, const std::vector<std::string>& tags) {
        WebPage page = WebPage::create(url, domain, title);
        Bookmark bookmark = Bookmark::create(page, tags);
        BookmarkManager manager = BookmarkManager::create();

        bool result = manager.addBookmark(bookmark);

        if (!result || manager.getBookmarks().empty() || manager.getBookmarks().front().getPage().getUrl() != url) {
            std::cerr << "TestBookmarkManagerAddBookmark failed." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkManagerAddBookmark passed." << std::endl;
        return 0;
    }

    // Test removing a bookmark from BookmarkManager
    int TestBookmarkManagerRemoveBookmark(const std::string& url, const std::string& domain, const std::string& title, const std::vector<std::string>& tags) {
        WebPage page = WebPage::create(url, domain, title);
        Bookmark bookmark = Bookmark::create(page, tags);
        BookmarkManager manager = BookmarkManager::create({ bookmark });

        bool result = manager.removeBookmark(0);

        if (!result || !manager.getBookmarks().empty()) {
            std::cerr << "TestBookmarkManagerRemoveBookmark failed." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkManagerRemoveBookmark passed." << std::endl;
        return 0;
    }
    int TestBookmarkManagerGetBookmarksByTag(const std::string& url1, const std::string& domain1, const std::string& title1, const std::vector<std::string>& tags1,
        const std::string& url2, const std::string& domain2, const std::string& title2, const std::vector<std::string>& tags2,
        const std::string& tagToFilter) {
        WebPage page1 = WebPage::create(url1, domain1, title1);
        WebPage page2 = WebPage::create(url2, domain2, title2);
        Bookmark bookmark1 = Bookmark::create(page1, tags1);
        Bookmark bookmark2 = Bookmark::create(page2, tags2);
        BookmarkManager manager = BookmarkManager::create({ bookmark1, bookmark2 });

        std::vector<Bookmark> filteredBookmarks = manager.getBookmarksByTag(tagToFilter);
        bool expectedTagPresent = (std::find(tags1.begin(), tags1.end(), tagToFilter) != tags1.end()) || (std::find(tags2.begin(), tags2.end(), tagToFilter) != tags2.end());

        if (expectedTagPresent && filteredBookmarks.empty()) {
            std::cerr << "TestBookmarkManagerGetBookmarksByTag failed (no bookmarks found)." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkManagerGetBookmarksByTag passed." << std::endl;
        return 0;
    }
    int TestTabManagerCreate() {
        TabManager manager = TabManager::create();

        if (manager.getCurrentTab().has_value()) {
            std::cerr << "TestTabManagerCreate failed." << std::endl;
            return 1;
        }

        std::cout << "TestTabManagerCreate passed." << std::endl;
        return 0;
    }
    int TestTabManagerAddTab(const std::string& url, const std::string& domain, const std::string& title) {
        WebPage page = WebPage::create(url, domain, title);
        Tab tab = Tab::create();
        tab.setCurrentPage(page, true);

        TabManager manager = TabManager::create();
        bool result = manager.addTab(tab);

        if (!result || !manager.getCurrentTab() || manager.getCurrentTab()->getCurrentPage()->getUrl() != url) {
            std::cerr << "TestTabManagerAddTab failed." << std::endl;
            return 1;
        }

        std::cout << "TestTabManagerAddTab passed." << std::endl;
        return 0;
    }
    int TestTabManagerSwitchTabs(const std::string& url1, const std::string& domain1, const std::string& title1,
        const std::string& url2, const std::string& domain2, const std::string& title2) {
        WebPage page1 = WebPage::create(url1, domain1, title1);
        WebPage page2 = WebPage::create(url2, domain2, title2);

        Tab tab1 = Tab::create();
        Tab tab2 = Tab::create();
        tab1.setCurrentPage(page1, true);
        tab2.setCurrentPage(page2, true);

        TabManager manager = TabManager::create({ tab1, tab2 });

        manager.moveToRightTab(); // Move to second tab
        if (!manager.getCurrentTab() || manager.getCurrentTab()->getCurrentPage()->getUrl() != url2) {
            std::cerr << "TestTabManagerSwitchTabs failed (move to right)." << std::endl;
            return 1;
        }

        manager.moveToLeftTab(); // Move back to first tab
        if (!manager.getCurrentTab() || manager.getCurrentTab()->getCurrentPage()->getUrl() != url1) {
            std::cerr << "TestTabManagerSwitchTabs failed (move to left)." << std::endl;
            return 1;
        }

        std::cout << "TestTabManagerSwitchTabs passed." << std::endl;
        return 0;
    }
    int TestTabManagerAddPageToTab(const std::string& url1, const std::string& domain1, const std::string& title1,
        const std::string& url2, const std::string& domain2, const std::string& title2) {
        WebPage page1 = WebPage::create(url1, domain1, title1);
        WebPage page2 = WebPage::create(url2, domain2, title2);

        Tab tab = Tab::create();
        tab.setCurrentPage(page1, true);
        TabManager manager = TabManager::create({ tab });

        bool result = manager.addPageToTab(page2);

        if (!result || !manager.getCurrentTab() || manager.getCurrentTab()->getCurrentPage()->getUrl() != url2) {
            std::cerr << "TestTabManagerAddPageToTab failed." << std::endl;
            return 1;
        }

        std::cout << "TestTabManagerAddPageToTab passed." << std::endl;
        return 0;
    }

} // namespace Tests

int main(int argc, char* argv[]) {
    int result = 0;

    if (argc > 1) {
        std::string testName = argv[1];

        if (testName == "TestWebPageConstructor") {

            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            result += Tests::TestWebPageConstructor(url, domain, title);
        }
        else if (testName == "TestBookmarkCreate") {

            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            std::vector<std::string> tags;
            for (int i = 5; i < argc; ++i) {
                tags.push_back(argv[i]);
            }
            result += Tests::TestBookmarkCreate(url, domain, title, tags);
        }
        else if (testName == "TestBookmarkHasTag") {
            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            std::string tagToCheck = argv[argc - 1];
            std::vector<std::string> tags;
            for (int i = 5; i < argc - 1; ++i) {
                tags.push_back(argv[i]);
            }
            result += Tests::TestBookmarkHasTag(url, domain, title, tags, tagToCheck);
        }
        else if (testName == "TestHistoryConstructor") {
            std::string url1 = argv[2];
            std::string domain1 = argv[3];
            std::string title1 = argv[4];
            std::string url2 = argv[5];
            std::string domain2 = argv[6];
            std::string title2 = argv[7];
            result += Tests::TestHistoryConstructor(url1, domain1, title1, url2, domain2, title2);
        }
        else if (testName == "TestHistoryAddPage") {

            std::string url1 = argv[2];
            std::string domain1 = argv[3];
            std::string title1 = argv[4];
            std::string url2 = argv[5];
            std::string domain2 = argv[6];
            std::string title2 = argv[7];
            result += Tests::TestHistoryAddPage(url1, domain1, title1, url2, domain2, title2);
        }
        else if (testName == "TestBookmarkManagerCreate") {
            result += Tests::TestBookmarkManagerCreate();

        }
        else if (testName == "TestBookmarkManagerAddBookmark") {

            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            std::vector<std::string> tags;
            for (int i = 5; i < argc; ++i) {
                tags.push_back(argv[i]);
            }
            result += Tests::TestBookmarkManagerAddBookmark(url, domain, title, tags);
        }
        else if (testName == "TestBookmarkManagerRemoveBookmark") {

            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            std::vector<std::string> tags;
            for (int i = 5; i < argc; ++i) {
                tags.push_back(argv[i]);
            }
            result += Tests::TestBookmarkManagerRemoveBookmark(url, domain, title, tags);
        }
        else if (testName == "TestBookmarkManagerGetBookmarksByTag") {

            std::string url1 = argv[2];
            std::string domain1 = argv[3];
            std::string title1 = argv[4];
            std::vector<std::string> tags1;
            int i;
            for (i = 5; i < argc - 5; ++i) {
                tags1.push_back(argv[i]);
            }
            std::string url2 = argv[i];
            std::string domain2 = argv[i + 1];
            std::string title2 = argv[i + 2];
            std::string tagToFilter = argv[i + 3];

            result += Tests::TestBookmarkManagerGetBookmarksByTag(url1, domain1, title1, tags1, url2, domain2, title2, tags1, tagToFilter);
        }
        else if (testName == "TestTabManagerCreate") {
            result += Tests::TestTabManagerCreate();
        }
        else if (testName == "TestTabManagerAddTab") {

            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            result += Tests::TestTabManagerAddTab(url, domain, title);
        }
        else if (testName == "TestTabManagerSwitchTabs") {

            std::string url1 = argv[2];
            std::string domain1 = argv[3];
            std::string title1 = argv[4];
            std::string url2 = argv[5];
            std::string domain2 = argv[6];
            std::string title2 = argv[7];
            result += Tests::TestTabManagerSwitchTabs(url1, domain1, title1, url2, domain2, title2);
        }
        else if (testName == "TestTabManagerAddPageToTab") {

            std::string url1 = argv[2];
            std::string domain1 = argv[3];
            std::string title1 = argv[4];
            std::string url2 = argv[5];
            std::string domain2 = argv[6];
            std::string title2 = argv[7];
            result += Tests::TestTabManagerAddPageToTab(url1, domain1, title1, url2, domain2, title2);
        }
        else {
            std::cerr << "Unknown test name: " << testName << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "No test name provided!" << std::endl;
        return 1;
    }

    return result;
}
