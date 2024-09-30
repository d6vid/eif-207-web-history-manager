add_library(controllers STATIC
    BrowserController.cpp)

target_include_directories(controllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})