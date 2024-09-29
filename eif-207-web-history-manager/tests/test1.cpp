#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <chrono>
#include "../../model/WebPage.h"  
#include "../../model/History.h"
#include "../../model/Policy.h"
#include "../../model/Bookmark.h"

namespace Tests {

    int CreateWebPageTest() {
        const std::string expectedUrl = "https://example.com";
        const std::string expectedDomain = "example.com";
        const std::string expectedTitle = "Example Title";

        WebPage actual = WebPage::create(expectedUrl, expectedDomain, expectedTitle);

        if (expectedUrl != actual.getUrl()) {
            std::cerr << "CreateWebPageTest failed: expected URL " << expectedUrl
                << ", but got " << actual.getUrl() << std::endl;
            return 1;
        }

        if (expectedDomain != actual.getDomain()) {
            std::cerr << "CreateWebPageTest failed: expected Domain " << expectedDomain
                << ", but got " << actual.getDomain() << std::endl;
            return 1;
        }

        if (expectedTitle != actual.getTitle()) {
            std::cerr << "CreateWebPageTest failed: expected Title " << expectedTitle
                << ", but got " << actual.getTitle() << std::endl;
            return 1;
        }

        std::cout << "CreateWebPageTest passed!" << std::endl;
        return 0;
    }

    int TestHistoryCreate() {
        std::deque<WebPage> pages = {
            WebPage::create("https://page1.com", "page1.com", "Page 1"),
            WebPage::create("https://page2.com", "page2.com", "Page 2")
        };
        size_t currentIndex = 1;

        History history = History::create(pages, currentIndex);

        if (history.getCurrentPage()->getUrl() != "https://page2.com") {
            std::cerr << "TestHistoryCreate failed: expected current URL to be 'https://page2.com' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        std::cout << "TestHistoryCreate passed!" << std::endl;
        return 0;
    }

    int TestHistoryAddPage() {
        std::deque<WebPage> pages = { WebPage::create("https://initialpage.com", "initialpage.com", "Initial Page") };
        History history = History::create(pages);

        WebPage newPage = WebPage::create("https://newpage.com", "newpage.com", "New Page");
        history.addPage(newPage);

        if (history.getCurrentPage()->getUrl() != "https://newpage.com") {
            std::cerr << "TestHistoryAddPage failed: expected current URL to be 'https://newpage.com' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        std::cout << "TestHistoryAddPage passed!" << std::endl;
        return 0;
    }

    int TestHistoryNavigation() {
        std::deque<WebPage> pages = {
            WebPage::create("https://page1.com", "page1.com", "Page 1"),
            WebPage::create("https://page2.com", "page2.com", "Page 2"),
            WebPage::create("https://page3.com", "page3.com", "Page 3")
        };
        History history = History::create(pages, 2);

        history.moveToLeftPage();
        if (history.getCurrentPage()->getUrl() != "https://page2.com") {
            std::cerr << "TestHistoryNavigation failed: expected current URL to be 'https://page2.com' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        history.moveToLeftPage();
        if (history.getCurrentPage()->getUrl() != "https://page1.com") {
            std::cerr << "TestHistoryNavigation failed: expected current URL to be 'https://page1.com' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        if (history.moveToLeftPage()) {
            std::cerr << "TestHistoryNavigation failed: expected not to be able to move further left" << std::endl;
            return 1;
        }

        history.moveToRightPage();
        if (history.getCurrentPage()->getUrl() != "https://page2.com") {
            std::cerr << "TestHistoryNavigation failed: expected current URL to be 'https://page2.com' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        std::cout << "TestHistoryNavigation passed!" << std::endl;
        return 0;
    }

    int TestPolicyLimit() {
        Policy policy(3, std::chrono::seconds(60));
        std::vector<std::string> history = { "page1", "page2", "page3", "page4", "page5" };

        policy.limit(history);

        if (history.size() != 3) {
            std::cerr << "TestPolicyLimit failed: expected history size to be 3, but got " << history.size() << std::endl;
            return 1;
        }

        if (history[0] != "page3" || history[1] != "page4" || history[2] != "page5") {
            std::cerr << "TestPolicyLimit failed: history content is incorrect after applying limit." << std::endl;
            return 1;
        }

        std::cout << "TestPolicyLimit passed!" << std::endl;
        return 0;
    }

    int TestPolicyClean() {
        Policy policy(5, std::chrono::seconds(60));

        auto now = std::chrono::system_clock::now();
        std::vector<std::pair<std::string, std::chrono::system_clock::time_point>> historyTimestamps = {
            {"page1", now - std::chrono::minutes(2)},
            {"page2", now - std::chrono::minutes(1)},
            {"page3", now - std::chrono::seconds(30)},
            {"page4", now}
        };

        policy.clean(historyTimestamps);

        if (historyTimestamps.size() != 2) {
            std::cerr << "TestPolicyClean failed: expected 2 valid entries, but got " << historyTimestamps.size() << std::endl;
            return 1;
        }

        if (historyTimestamps[0].first != "page3" || historyTimestamps[1].first != "page4") {
            std::cerr << "TestPolicyClean failed: history content is incorrect after cleaning." << std::endl;
            return 1;
        }

        std::cout << "TestPolicyClean passed!" << std::endl;
        return 0;
    }

    int TestBookmarkCreate() {
        WebPage page = WebPage::create("https://example.com", "example.com", "Example Page");
        std::vector<std::string> tags = { "important", "reference" };

        Bookmark bookmark = Bookmark::create(page, tags);

        if (bookmark.getPage().getUrl() != "https://example.com") {
            std::cerr << "TestBookmarkCreate failed: expected page URL to be 'https://example.com' but got '"
                << bookmark.getPage().getUrl() << "'" << std::endl;
            return 1;
        }

        if (bookmark.getTags().size() != 2 || bookmark.getTags()[0] != "important" || bookmark.getTags()[1] != "reference") {
            std::cerr << "TestBookmarkCreate failed: expected tags to be 'important' and 'reference', but got different tags."
                << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkCreate passed!" << std::endl;
        return 0;
    }
    int TestBookmarkHasTag() {
        WebPage page = WebPage::create("https://example.com", "example.com", "Example Page");
        std::vector<std::string> tags = { "important", "reference" };
        Bookmark bookmark = Bookmark::create(page, tags);

        if (!bookmark.hasTag("important")) {
            std::cerr << "TestBookmarkHasTag failed: expected tag 'important' to be found but it was not." << std::endl;
            return 1;
        }

        if (bookmark.hasTag("random")) {
            std::cerr << "TestBookmarkHasTag failed: expected tag 'random' to not be found but it was." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkHasTag passed!" << std::endl;
        return 0;
    }

    int TestBookmarkGetTags() {
        WebPage page = WebPage::create("https://example.com", "example.com", "Example Page");
        std::vector<std::string> tags = { "tag1", "tag2", "tag3" };
        Bookmark bookmark = Bookmark::create(page, tags);

        const std::vector<std::string>& retrievedTags = bookmark.getTags();

        if (retrievedTags.size() != 3 || retrievedTags[0] != "tag1" || retrievedTags[1] != "tag2" || retrievedTags[2] != "tag3") {
            std::cerr << "TestBookmarkGetTags failed: expected tags 'tag1', 'tag2', 'tag3', but got different values."
                << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkGetTags passed!" << std::endl;
        return 0;
    }
  
    int TestPolicyGetSetMax() {
        Policy policy(5, std::chrono::seconds(60));

        policy.setmax(10);

        if (policy.getmax() != 10) {
            std::cerr << "TestPolicyGetSetMax failed: expected max to be 10, but got " << policy.getmax() << std::endl;
            return 1;
        }

        std::cout << "TestPolicyGetSetMax passed!" << std::endl;
        return 0;
    }

    int TestPolicyGetSetDuration() {
        Policy policy(5, std::chrono::seconds(120));

        policy.setduration(std::chrono::seconds(120));

        if (policy.getduration() != std::chrono::seconds(120)) {
            std::cerr << "TestPolicyGetSetDuration failed: expected duration to be 120 seconds, but got "
                << policy.getduration().count() << " seconds." << std::endl;
            return 1;
        }

        std::cout << "TestPolicyGetSetDuration passed!" << std::endl;
        return 0;
    }
} 
int main(int argc, char* argv[]) {
    int result = 0;

    if (argc > 1) {
        std::string testName = argv[1];

        if (testName == "CreateWebPageTest") {
            result += Tests::CreateWebPageTest();
        }
        else if (testName == "TestHistoryCreate") {
            result += Tests::TestHistoryCreate();
        }
        else if (testName == "TestHistoryAddPage") {
            result += Tests::TestHistoryAddPage();
        }
        else if (testName == "TestHistoryNavigation") {
            result += Tests::TestHistoryNavigation();
        }
        else if (testName == "TestPolicyLimit") {
            result += Tests::TestPolicyLimit();
        }
        else if (testName == "TestPolicyClean") {
            result += Tests::TestPolicyClean();
        }
        else if (testName == "TestPolicyGetSetMax") {
            result += Tests::TestPolicyGetSetMax();
        }
        else if (testName == "TestPolicyGetSetDuration") {
            result += Tests::TestPolicyGetSetDuration();
        }
        else if (testName == "TestBookmarkCreate") {
            result += Tests::TestBookmarkCreate();
        }
        else if (testName == "TestBookmarkHasTag") {
            result += Tests::TestBookmarkHasTag();
        }
        else if (testName == "TestBookmarkGetTags") {
            result += Tests::TestBookmarkGetTags();
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
