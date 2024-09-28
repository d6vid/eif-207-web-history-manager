add_library(serializers STATIC
    WebPageSerializer.cpp
)

target_include_directories(serializers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})