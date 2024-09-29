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

    int CreateWebPageTest(const std::string& expectedUrl, const std::string& expectedDomain, const std::string& expectedTitle) {
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
    int TestHistoryCreate(const std::string& url1, const std::string& domain1, const std::string& title1,
        const std::string& url2, const std::string& domain2, const std::string& title2,
        size_t currentIndex) {
        std::deque<WebPage> pages = {
            WebPage::create(url1, domain1, title1),
            WebPage::create(url2, domain2, title2)
        };

        History history = History::create(pages, currentIndex);

        if (history.getCurrentPage()->getUrl() != url2) {
            std::cerr << "TestHistoryCreate failed: expected current URL to be '" << url2 << "' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        std::cout << "TestHistoryCreate passed!" << std::endl;
        return 0;
    }


    int TestHistoryAddPage(const std::string& initialUrl, const std::string& initialDomain, const std::string& initialTitle,
        const std::string& newUrl, const std::string& newDomain, const std::string& newTitle) {
        std::deque<WebPage> pages = { WebPage::create(initialUrl, initialDomain, initialTitle) };
        History history = History::create(pages);

        WebPage newPage = WebPage::create(newUrl, newDomain, newTitle);
        history.addPage(newPage);

        if (history.getCurrentPage()->getUrl() != newUrl) {
            std::cerr << "TestHistoryAddPage failed: expected current URL to be '" << newUrl << "' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        std::cout << "TestHistoryAddPage passed!" << std::endl;
        return 0;
    }

    int TestHistoryNavigation(const std::string& page1Url, const std::string& page2Url, const std::string& page3Url) {
        std::deque<WebPage> pages = {
            WebPage::create(page1Url, "page1.com", "Page 1"),
            WebPage::create(page2Url, "page2.com", "Page 2"),
            WebPage::create(page3Url, "page3.com", "Page 3")
        };
        History history = History::create(pages, 2);

        history.moveToLeftPage();
        if (history.getCurrentPage()->getUrl() != page2Url) {
            std::cerr << "TestHistoryNavigation failed: expected current URL to be '" << page2Url << "' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        history.moveToLeftPage();
        if (history.getCurrentPage()->getUrl() != page1Url) {
            std::cerr << "TestHistoryNavigation failed: expected current URL to be '" << page1Url << "' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        if (history.moveToLeftPage()) {
            std::cerr << "TestHistoryNavigation failed: expected not to be able to move further left" << std::endl;
            return 1;
        }

        history.moveToRightPage();
        if (history.getCurrentPage()->getUrl() != page2Url) {
            std::cerr << "TestHistoryNavigation failed: expected current URL to be '" << page2Url << "' but got '"
                << history.getCurrentPage()->getUrl() << "'" << std::endl;
            return 1;
        }

        std::cout << "TestHistoryNavigation passed!" << std::endl;
        return 0;
    }

    int TestPolicyLimit(int maxSize, const std::vector<std::string>& historyInput) {
        Policy policy(maxSize, std::chrono::seconds(60));
        std::vector<std::string> history = historyInput;

        policy.limit(history);

        if (history.size() != static_cast<size_t>(maxSize)) {
            std::cerr << "TestPolicyLimit failed: expected history size to be " << maxSize << ", but got " << history.size() << std::endl;
            return 1;
        }

        std::cout << "TestPolicyLimit passed!" << std::endl;
        return 0;
    }

    int TestPolicyClean(int maxEntries, int durationInSeconds, int timeDiff1, int timeDiff2, int timeDiff3, int timeDiff4) {
        Policy policy(maxEntries, std::chrono::seconds(durationInSeconds));

        auto now = std::chrono::system_clock::now();
        std::vector<std::pair<std::string, std::chrono::system_clock::time_point>> historyTimestamps = {
            {"page1", now - std::chrono::seconds(timeDiff1)},  
            {"page2", now - std::chrono::seconds(timeDiff2)},  
            {"page3", now - std::chrono::seconds(timeDiff3)},  
            {"page4", now - std::chrono::seconds(timeDiff4)}   
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

    int TestBookmarkCreate(const std::string& url, const std::string& domain, const std::string& title, const std::vector<std::string>& tags) {
        WebPage page = WebPage::create(url, domain, title);
        Bookmark bookmark = Bookmark::create(page, tags);

        if (bookmark.getPage().getUrl() != url) {
            std::cerr << "TestBookmarkCreate failed: expected page URL to be '" << url << "' but got '"
                << bookmark.getPage().getUrl() << "'" << std::endl;
            return 1;
        }

        if (bookmark.getTags().size() != tags.size() || bookmark.getTags() != tags) {
            std::cerr << "TestBookmarkCreate failed: expected tags, but got different values." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkCreate passed!" << std::endl;
        return 0;
    }

    int TestBookmarkGetTags(const std::string& url, const std::string& domain, const std::string& title, const std::vector<std::string>& expectedTags) {
        WebPage page = WebPage::create(url, domain, title);
        Bookmark bookmark = Bookmark::create(page, expectedTags);

        const std::vector<std::string>& retrievedTags = bookmark.getTags();

        if (retrievedTags.size() != expectedTags.size()) {
            std::cerr << "TestBookmarkGetTags failed: expected " << expectedTags.size() << " tags, but got " << retrievedTags.size() << std::endl;
            return 1;
        }

        for (size_t i = 0; i < expectedTags.size(); ++i) {
            if (retrievedTags[i] != expectedTags[i]) {
                std::cerr << "TestBookmarkGetTags failed: expected tag '" << expectedTags[i] << "', but got '" << retrievedTags[i] << "'." << std::endl;
                return 1;
            }
        }

        std::cout << "TestBookmarkGetTags passed!" << std::endl;
        return 0;
    }


    int TestBookmarkHasTag(const std::string& url, const std::string& domain, const std::string& title, const std::string& tag, const std::string& checkTag) {
        WebPage page = WebPage::create(url, domain, title);
        std::vector<std::string> tags = { tag };
        Bookmark bookmark = Bookmark::create(page, tags);

        if (!bookmark.hasTag(tag)) {
            std::cerr << "TestBookmarkHasTag failed: expected tag '" << tag << "' to be found but it was not." << std::endl;
            return 1;
        }

        if (bookmark.hasTag(checkTag)) {
            std::cerr << "TestBookmarkHasTag failed: expected tag '" << checkTag << "' to not be found but it was." << std::endl;
            return 1;
        }

        std::cout << "TestBookmarkHasTag passed!" << std::endl;
        return 0;
    }

  
    int TestPolicyGetSetMax(int max) {
        Policy policy(5, std::chrono::seconds(60));

        policy.setmax(max);

        if (policy.getmax() != max) {
            std::cerr << "TestPolicyGetSetMax failed: expected max to be " << max << ", but got " << policy.getmax() << std::endl;
            return 1;
        }

        std::cout << "TestPolicyGetSetMax passed!" << std::endl;
        return 0;
    }

    int TestPolicyGetSetDuration(int duration) {
        Policy policy(5, std::chrono::seconds(120));

        policy.setduration(std::chrono::seconds(duration));

        if (policy.getduration() != std::chrono::seconds(duration)) {
            std::cerr << "TestPolicyGetSetDuration failed: expected duration to be " << duration
                << " seconds, but got " << policy.getduration().count() << " seconds." << std::endl;
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
           
            std::string expectedUrl = argv[2];
            std::string expectedDomain = argv[3];
            std::string expectedTitle = argv[4];
            result += Tests::CreateWebPageTest(expectedUrl, expectedDomain, expectedTitle);
        }
        else if (testName == "TestHistoryCreate") {
            std::string url1 = argv[2];
            std::string domain1 = argv[3];
            std::string title1 = argv[4];
            std::string url2 = argv[5];
            std::string domain2 = argv[6];
            std::string title2 = argv[7];
            size_t currentIndex = std::stoul(argv[8]);
            result += Tests::TestHistoryCreate(url1, domain1, title1, url2, domain2, title2, currentIndex);
        }
        else if (testName == "TestHistoryAddPage") {
            std::string initialUrl = argv[2];
            std::string initialDomain = argv[3];
            std::string initialTitle = argv[4];
            std::string newUrl = argv[5];
            std::string newDomain = argv[6];
            std::string newTitle = argv[7];
            result += Tests::TestHistoryAddPage(initialUrl, initialDomain, initialTitle, newUrl, newDomain, newTitle);
        }
        else if (testName == "TestHistoryNavigation") {
            std::string page1Url = argv[2];
            std::string page2Url = argv[3];
            std::string page3Url = argv[4];
            result += Tests::TestHistoryNavigation(page1Url, page2Url, page3Url);
        }
        else if (testName == "TestPolicyLimit") {
            int maxSize = std::stoi(argv[2]);  
            std::vector<std::string> historyInput;

            for (int i = 3; i < argc; ++i) {
                historyInput.push_back(argv[i]);
            }
            result += Tests::TestPolicyLimit(maxSize, historyInput);
        }
        else if (testName == "TestPolicyClean") {
            int maxEntries = std::stoi(argv[2]);
            int durationInSeconds = std::stoi(argv[3]);
            int timeDiff1 = std::stoi(argv[4]);
            int timeDiff2 = std::stoi(argv[5]);
            int timeDiff3 = std::stoi(argv[6]);
            int timeDiff4 = std::stoi(argv[7]);
            result += Tests::TestPolicyClean(maxEntries, durationInSeconds, timeDiff1, timeDiff2, timeDiff3, timeDiff4);
        }
        else if (testName == "TestPolicyGetSetMax") {
            int max = std::stoi(argv[2]);
            result += Tests::TestPolicyGetSetMax(max);
        }
        else if (testName == "TestPolicyGetSetDuration") {
            int duration = std::stoi(argv[2]);
            result += Tests::TestPolicyGetSetDuration(duration);
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
            std::vector<std::string> expectedTags;
            for (int i = 5; i < argc; ++i) {
                expectedTags.push_back(argv[i]);
            }
            result += Tests::TestBookmarkGetTags(url, domain, title, expectedTags);
        }
        else if (testName == "TestBookmarkGetTags") {
            std::string url = argv[2];
            std::string domain = argv[3];
            std::string title = argv[4];
            std::vector<std::string> expectedTags;
            for (int i = 5; i < argc; ++i) {
                expectedTags.push_back(argv[i]);
            }
            result += Tests::TestBookmarkGetTags(url, domain, title, expectedTags);
        
           
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
