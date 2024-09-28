add_library(managers STATIC
    BookmarkManager.cpp
    TabManager.cpp
    SearchManager.cpp
)

target_include_directories(managers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})