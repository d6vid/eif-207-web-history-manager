# testing en CMake
enable_testing()

# ejecutable
add_executable(test1 test1.cpp)

# Enlazamos con las bibliotecas
target_link_libraries(test1
  PRIVATE
    managers
    model
)
#test
add_test(NAME modeltest COMMAND test1)


