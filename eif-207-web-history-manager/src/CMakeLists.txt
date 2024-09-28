include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/managers
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers
)

add_subdirectory(model)
add_subdirectory(managers)
add_subdirectory(serializers)