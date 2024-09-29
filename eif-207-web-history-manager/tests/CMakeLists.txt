# testing en CMake
enable_testing()

# ejecutable
add_executable(test1 test1.cpp)

# Enlazar con las bibliotecas necesarias
target_link_libraries(test1
  PRIVATE
    managers
    model
)

# Agregar varias pruebas, pasando parámetros
add_test(NAME CreateWebPageTest COMMAND test1 CreateWebPageTest)
add_test(NAME TestHistoryCreate COMMAND test1 TestHistoryCreate)
add_test(NAME TestHistoryAddPage COMMAND test1 TestHistoryAddPage)
add_test(NAME TestHistoryNavigation COMMAND test1 TestHistoryNavigation)
add_test(NAME TestPolicyLimit COMMAND test1 TestPolicyLimit)
add_test(NAME TestPolicyClean COMMAND test1 TestPolicyClean)
add_test(NAME TestPolicyGetSetMax COMMAND test1 TestPolicyGetSetMax)
add_test(NAME TestPolicyGetSetDuration COMMAND test1 TestPolicyGetSetDuration)
add_test(NAME TestBookmarkCreate COMMAND test1 TestBookmarkCreate)
add_test(NAME TestBookmarkHasTag COMMAND test1 TestBookmarkHasTag)
add_test(NAME TestBookmarkGetTags COMMAND test1 TestBookmarkGetTags)
