add_library(web_manager STATIC
    WebPage.cpp
    History.cpp
    Tab.cpp
    Navegador.cpp
 "History.cpp" "History.h")

target_include_directories(web_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})