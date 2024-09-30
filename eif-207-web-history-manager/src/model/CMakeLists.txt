add_library(model STATIC
    WebPage.cpp
    Bookmark.cpp
    History.cpp
    Tab.cpp
 "Policy.h" "Policy.cpp")

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})