add_library(model STATIC
    WebPage.cpp
    Bookmark.cpp
    History.cpp
    Tab.cpp
    Policies.cpp
)

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})