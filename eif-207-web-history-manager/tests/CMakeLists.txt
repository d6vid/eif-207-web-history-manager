# Activamos la función de testing en CMake
enable_testing()

# Añadimos el ejecutable de los tests para test1.cpp
add_executable(test1 test1.cpp)

# Enlazamos con las bibliotecas de tu proyecto (managers y model)
target_link_libraries(test1
  PRIVATE
    managers
    model
)

# Añadimos el test al framework de CTest para test1.cpp
add_test(NAME CreateWebPageTest COMMAND test1)


# Añadimos otro ejecutable para test2.cpp
add_executable(test2 test2.cpp)

# Enlazamos con las mismas bibliotecas para el segundo test (managers y model)
target_link_libraries(test2
  PRIVATE
    managers
    model
)

# Añadimos el segundo test al framework de CTest para test2.cpp
add_test(NAME BookmarkManagerTest COMMAND test2)
