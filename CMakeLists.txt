cmake_minimum_required(VERSION 3.16)

project(ElectechInnovation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Zéro avertissement exigé par le cahier des charges (EOO-10).
add_compile_options(-Wall -Wextra -pedantic)

# Bibliothèque du module de conversion des montants en lettres.
add_library(montant_lettres STATIC src/montant_lettres.cpp)
target_include_directories(montant_lettres PUBLIC include)

# Programme principal.
add_executable(electech src/main.cpp)
target_link_libraries(electech PRIVATE montant_lettres)

# Tests unitaires (doctest), lancés par « ctest ».
enable_testing()
add_executable(test_montant_lettres tests/test_montant_lettres.cpp)
target_include_directories(test_montant_lettres PRIVATE tests)
target_link_libraries(test_montant_lettres PRIVATE montant_lettres)
add_test(NAME montant_lettres COMMAND test_montant_lettres)
