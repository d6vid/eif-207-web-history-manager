include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# testing en CMake
enable_testing()
# ejecutable
add_executable(test1 test1.cpp)
# bibliotecas 
target_link_libraries(test1
  PRIVATE
    managers
    model
)
# tests pasando parametros
add_test(NAME TestWebPageConstructor COMMAND test1 TestWebPageConstructor "https://example.com" "example.com" "Example Title")
add_test(NAME TestBookmarkCreate COMMAND test1 TestBookmarkCreate "https://example.com" "example.com" "Example Page" "important" "reference")
add_test(NAME TestBookmarkHasTag COMMAND test1 TestBookmarkHasTag "https://example.com" "example.com" "Example Page" "tag1" "tag2" "tag1")
add_test(NAME TestHistoryAddPage COMMAND test1 TestHistoryAddPage "https://page1.com" "page1.com" "Title 1" "https://page2.com" "page2.com" "Title 2")
add_test(NAME TestBookmarkManagerCreate COMMAND test1 TestBookmarkManagerCreate)
add_test(NAME TestBookmarkManagerAddBookmark COMMAND test1 TestBookmarkManagerAddBookmark "https://example.com" "example.com" "Example Page" "tag1" "tag2")
add_test(NAME TestBookmarkManagerRemoveBookmark COMMAND test1 TestBookmarkManagerRemoveBookmark "https://example.com" "example.com" "Example Page" "tag1" "tag2")
add_test(NAME TestBookmarkManagerGetBookmarksByTag COMMAND test1 TestBookmarkManagerGetBookmarksByTag "https://example1.com" "example1.com" "Title 1" "tag1" "https://example2.com" "example2.com" "Title 2" "tag1")
add_test(NAME TestTabManagerCreate COMMAND test1 TestTabManagerCreate)
add_test(NAME TestTabManagerAddTab COMMAND test1 TestTabManagerAddTab "https://example.com" "example.com" "Example Page")
add_test(NAME TestTabManagerSwitchTabs COMMAND test1 TestTabManagerSwitchTabs "https://example1.com" "example1.com" "Title 1" "https://example2.com" "example2.com" "Title 2")
add_test(NAME TestTabManagerAddPageToTab COMMAND test1 TestTabManagerAddPageToTab "https://example1.com" "example1.com" "Title 1" "https://example2.com" "example2.com" "Title 2")