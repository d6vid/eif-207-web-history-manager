add_library(web_manager STATIC
    WebPage.cpp
    Bookmark.cpp
    BookmarkManager.cpp
    History.cpp
    Tab.cpp
    TabManager.cpp
    Browser.cpp
    Menu.cpp
 "SearchManager.h" "SearchManager.cpp")

target_include_directories(web_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})