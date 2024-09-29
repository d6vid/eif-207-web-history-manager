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
add_test(NAME CreateWebPageTest COMMAND test1 CreateWebPageTest "https://example.com" "example.com" "Example Title")
add_test(NAME TestHistoryCreate COMMAND test1 TestHistoryCreate "https://page1.com" "page1.com" "Page 1" "https://page2.com" "page2.com" "Page 2" 1)
add_test(NAME TestHistoryAddPage COMMAND test1 TestHistoryAddPage "https://initialpage.com" "initialpage.com" "Initial Page" "https://newpage.com" "newpage.com" "New Page")
add_test(NAME TestHistoryNavigation COMMAND test1 TestHistoryNavigation "https://page1.com" "https://page2.com" "https://page3.com")
add_test(NAME TestPolicyLimit COMMAND test1 TestPolicyLimit 3 "page1" "page2" "page3" "page4" "page5")
add_test(NAME TestPolicyClean COMMAND test1 TestPolicyClean 5 60 120 60 30 0)
add_test(NAME TestPolicyGetSetMax COMMAND test1 TestPolicyGetSetMax 10)
add_test(NAME TestPolicyGetSetDuration COMMAND test1 TestPolicyGetSetDuration 120)
add_test(NAME TestBookmarkCreate COMMAND test1 TestBookmarkCreate "https://example.com" "example.com" "Example Page" "important" "reference")
add_test(NAME TestBookmarkHasTag COMMAND test1 TestBookmarkHasTag "https://example.com" "example.com" "Example Page" "important" "random")
add_test(NAME TestBookmarkGetTags COMMAND test1 TestBookmarkGetTags "https://example.com" "example.com" "Example Page" "tag1" "tag2" "tag3")
